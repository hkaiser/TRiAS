/* --------------------------------------------------------------------------
 * BasicScript functions, types and definitions for BasicScript 2.25.
 *
 * Copyright (c) 1992-1996, Summit Software Company. All Rights Reserved.
 *
 * --------------------------------------------------------------------------
 * This module uses tabs 4,7
 * --------------------------------------------------------------------------
 *
 * This header file is portable among multiple platforms. To use this
 * header file for a particular platform, enable one of the following
 * defines before including this file:
 *
 *	#define			Platform
 *	---------------------------------------------------------------------
 *	EBWIN				Windows 3.1, Windows for WorkGroups
 *	EBMAC				Macintosh System 7.51 and PowerPC
 *	EBWIN32			32-Bit Windows: Win32s, Windows 95, Windows NT (Intel, MIPS, Alpha, PPC)
 *	EBSUNOS			SunOS 4.1.3C or higher
 *	EBSOLARIS		Solaris 2.4 or higher
 *	EBAIX				IBM AIX/6000 Version 3.2.5 or higher
 *	EBHPUX			HP-UX 9.03 or higher
 *	EBIRIX			SGI IRIX 5.2 or higher
 *	EBNLM				Netware Loadable Module (Verison 3.2 or above)
 *	EBOS2				IBM OS/2 (Version 2.0 or above)
 *	EBUNIXWARE		Novell UnixWare 1.1 and above
 *	EBSCO				SCO UNIX Release 3.2 and above
 *	EBOSF1			Digital OSF/1
 *	EBLINUX			Linux
 *	EBVMS				Digital OpenVMS (Alpha)
 *
 * --------------------------------------------------------------------------
 * Other defines:
 *
 *		EBWIDE			Defined for applications supporting wide characters.
 *							Currently available only when EBWIN32 is defined.
 *
 * ----------------------------------------------------------------------- */

#ifndef EBMAC	/* Mac doesn't like long #if statements */
#if defined(EBSUNOS) || defined(EBSOLARIS) || defined(EBAIX) || \
	defined(EBHPUX) || defined(EBIRIX) || \
	defined(EBUNIXWARE)|| defined(EBSCO)|| defined(EBOSF1) || defined(EBLINUX)
#define EBUNIX	/* used internally to simplify preprocessor directives */
#endif	/* all UNIX defines */
#endif	/* EBMAC */

/* make sure one of these is defined */
#ifndef EBMAC	/* Mac doesn't like long #if statements */
#if !defined(EBWIN) && \
	 !defined(EBMAC) && \
    !defined(EBWIN32) && \
    !defined(EBUNIX) && \
	 !defined(EBNLM) && \
	 !defined(EBOS2) && \
	 !defined(EBVMS)
#ifndef RC_INVOKED		/* ignore a bunch of stuff for the stupid resource compiler */
#error Platform not defined (e.g. EBWIN)
#endif	/* !RC_INVOKED */
#endif	/* any platform */
#endif	/* !EBMAC */

/* Don't include this header file more than once! */
#if !defined( _EB_H_ )
#define _EB_H_

/*
 * Define the version of this file. Possible values are:
 *
 *		EB20		BasicScript 2.0
 *		EB21		BasicScript 2.1
 *		EB22		BasucScript 2.2
 *		EB225		BasucScript 2.25
 */
#define EB225	/* BasicScript 2.25 */

/* Make a special consideration for C++ files. */
#ifdef __cplusplus
extern "C"
{
#endif	/* __cplusplus */

/* --------------------------------------------------------------------------
 * EBWIN		(special definitions for this platform)
 * ----------------------------------------------------------------------- */
#ifdef EBWIN
#ifndef RC_INVOKED		/* ignore a bunch of stuff for the stupid resource compiler */

/*
 * Included these header files -- declarations that follow make use of these.
 * Including these header files twice will have no ill-effects.
 */
#include <windows.h>
#include <windowsx.h>

#ifdef __cplusplus
#undef LockData
#undef UnlockData

inline HANDLE LockData(UINT udummy)
{
	return ::LockSegment((UINT)-1);
}

inline void UnlockData(UINT udummy)
{
	::UnlockSegment((UINT)-1);
}
#endif /* __cplusplus */

#define ebFAR FAR
#define ebNEAR NEAR
#define ebAPI PASCAL FAR
#define ebCAPI CDECL FAR
#define ebCALLBACK PASCAL FAR
#define STRCPY lstrcpy

typedef unsigned long ebPARAM1;
typedef long ebPARAM2;

#define ebDECLARE_HANDLE(name)		struct name##__ { int unused; }; \
												typedef const struct name##__ NEAR* name
#define ebLITTLE_ENDIAN
#define WANT_PACK
#define ebWPARAM WPARAM
#define ebLPARAM LPARAM
#define ebHWND HWND
#define ebHFONT HFONT
#define ebLRESULT LRESULT
#define ebMSG UINT
#define ebMAKELPARAM MAKELPARAM
#define ebMAKELONG MAKELONG
#define ebHAVE_OLE				/* this platform supports OLE 2.0 automation */
#define ebCOLOR COLORREF
#define ebHCURSOR HCURSOR
typedef int ebINT;
typedef unsigned int ebUINT;

#endif	/* !RC_INVOKED */
#endif	/* EBWIN */

/* --------------------------------------------------------------------------
 * EBWIN32		(special definitions for this platform)
 * ----------------------------------------------------------------------- */
#ifdef EBWIN32
#ifndef RC_INVOKED

/*
 * Included these header files -- declarations that follow make use of these.
 * Including these header files twice will have no ill-effects.
 */
#include <windows.h>
#include <windowsx.h>

#define ebFAR
#define ebNEAR
#define ebAPI WINAPI
#define ebCAPI CDECL
#define ebCALLBACK CALLBACK
#define STRCPY strcpy
#define ebDECLARE_HANDLE(name) typedef short name
#if defined(EBMAINWIN) && !defined(alpha) && !defined(i86)
#define ebBIG_ENDIAN
#else
#define ebLITTLE_ENDIAN
#endif /* EBMAINWIN && !alpha */
#define ebMT	/* Win32 supports multiple-threads within the same instance */
typedef ULONG ebPARAM1;
typedef LONG ebPARAM2;
#define ebWPARAM WPARAM
#define ebLPARAM LPARAM
#define ebHWND HWND
#define ebHFONT HFONT
#define ebLRESULT LRESULT
#define ebMSG UINT
#define ebHAVE_OLE				/* this platform supports OLE 2.0 automation */
#define ebMAKELPARAM MAKELPARAM
#define ebMAKELONG MAKELONG
#define ebCOLOR COLORREF
#define ebHCURSOR HCURSOR
typedef int ebINT;
typedef unsigned int ebUINT;

#ifdef _X86_
/* pack these structures on Intel platforms */
#define WANT_PACK
#endif	/* _X86_ */

#ifdef _WIN64
#define EB64BIT
#endif /* _WIN64 */

#endif	/* !RC_INVOKED */
#endif	/* EBWIN32 */

/* --------------------------------------------------------------------------
 * EBOS2		(special definitions for this platform)
 * ----------------------------------------------------------------------- */
#ifdef EBOS2

/* include these lines for resource compiles */
#define BUILTINS 		  1001		 /* arbitrary unique resource id */
#define EXTENSIONINFO  1002		 /* arbitrary unique resource id */

#ifndef RC_INVOKED		/* ignore rest of stuff for resource compiler */

#ifndef INCL_WIN
#define INCL_WIN
#include <os2.h>
#endif	/* !INCL_WIN */

#define ebFAR
#define ebNEAR
#define ebAPI		 	  EXPENTRY   /* _System calling convention */
#define ebCAPI		 	  EXPENTRY   /* _System calling convention */
#define ebCALLBACK 	  EXPENTRY   /* _System calling convention */
#define STRCPY 		  strcpy
#define ebDECLARE_HANDLE(name) typedef unsigned short name
#define ebLITTLE_ENDIAN
#define ebMT	/* OS/2 supports multiple-threads within the same instance */
typedef ULONG ebPARAM1;
typedef LONG ebPARAM2;
typedef char* ebHFONT;
#define ebWPARAM MPARAM
#define ebLPARAM MPARAM
#define ebHWND HWND
#define ebLRESULT MRESULT
#define ebMAKELPARAM MPFROM2SHORT
#define ebMAKELONG MPFROM2SHORT
#define ebMSG ULONG
#define ebCOLOR ULONG
#define ebHCURSOR HCURSOR
typedef int ebINT;
typedef unsigned int ebUINT;

#endif	/* !RC_INVOKED */
#endif	/* EBOS2 */

/* --------------------------------------------------------------------------
 * UNIX/VMS		(special definitions for these platforms)
 * ----------------------------------------------------------------------- */
#if defined(EBUNIX) || defined(EBVMS)
#ifndef RC_INVOKED

#ifdef EBSOLARIS
#define ebMT		/* this platform supports multiple threads in the same process */
#endif	/* EBSOLARIS */

#define ebDECLARE_HANDLE(name)		typedef unsigned short name
#define ebDECLARE_HANDLEPLAT(name)	struct name##__ { int unused; }; \
													typedef struct name##__ * name

ebDECLARE_HANDLEPLAT( ebHWND );

typedef int ebINT;
typedef unsigned int ebUINT;

#define ebMSG ebUINT
#define ebWPARAM long
#define ebLPARAM long
#define ebLRESULT long
#define ebCOLOR long
typedef long ebHFONT;
typedef long ebHCURSOR;

#define ebFAR
#define ebNEAR
#define ebAPI
#define ebCAPI
#define ebCALLBACK
#define STRCPY strcpy

typedef unsigned long ebPARAM1;
typedef long ebPARAM2;

#define ebMAKELONG(a,b) (ebLPARAM)((ebLONG)(((ebWORD)(a))|((ebDWORD)((ebWORD)(b)))<<16))
#define ebMAKELPARAM(a,b) ((ebLPARAM)ebMAKELONG((a),(b)))

#if defined(EBSCO) || defined(EBUNIXWARE) || defined(EBOSF1) || defined(EBVMS) || defined(EBLINUX)
#define ebLITTLE_ENDIAN
#else	/* default is big endian */
#define ebBIG_ENDIAN
#endif	/* EBSCO || EBUNIXWARE || EBOSF1 || EBVMS */

#ifdef EBOSF1
#define EB64BIT
#endif	/* EBOSF1 */

#endif	/* !RC_INVOKED */
#endif	/* EBUNIX || EBVMS */

/* --------------------------------------------------------------------------
 * Netware	(special definitions for this platform)
 * ----------------------------------------------------------------------- */
#if defined(EBNLM)
#ifndef RC_INVOKED
#define ebFAR
#define ebNEAR
#define ebAPI
#define ebCAPI
#define ebCALLBACK
#define STRCPY strcpy
#define ebDECLARE_HANDLE(name) typedef unsigned short name
#define ebLITTLE_ENDIAN
typedef int ebHWND;
typedef unsigned long ebPARAM1;
typedef long ebPARAM2;
#define ebMSG ebUINT
#define ebWPARAM long
#define ebLPARAM long
#define ebLRESULT long
typedef int ebINT;
typedef unsigned int ebUINT;

#ifndef NULL
#define NULL	0
#endif /* !def NULL */

#endif	/* !RC_INVOKED */
#endif	/* EBNLM */

/* --------------------------------------------------------------------------
 * Macintosh		(special definitions for this platform)
 * ----------------------------------------------------------------------- */
#ifdef EBMAC
	#ifdef REZ
		#define RC_INVOKED	/* this head file uses RC_INVOKED instead of REZ */
	#endif	/* RC_INVOKED */
#endif	/* EBMAC */

#ifndef RC_INVOKED
#ifdef EBMAC

#ifdef __MWERKS__
/*   Switches to the MPW/Macintosh Toolbox calling convention.  Functions return 
 *   pointers in register D0.  68K Macintosh only.  
 */
#pragma pointers_in_D0
#if defined(EBMAC) && !defined(powerc) && !defined(__powerc)
#else
#pragma options align=mac68K
#endif
#endif	/* __MWERKS__ */

#ifndef __QUICKDRAW__
#include <QuickDraw.h>
#endif	/* __QUICKDRAW__ */

#ifndef __EVENTS__
#include <Events.h>
#endif	/* __ EVENTS__ */

#define ebFAR
#define ebNEAR
#define ebAPI
#define ebCAPI
#define ebCALLBACK
#define CALLBACK
#define STRCPY strcpy
#define ebDECLARE_HANDLE(name) typedef unsigned short name
#define ebBIG_ENDIAN
typedef unsigned long ebPARAM1;
typedef long ebPARAM2;
typedef long ebINT;
typedef unsigned long ebUINT;
typedef void *ebHFONT;
typedef struct tagMACFONT {
	short txFont;
	ebINT size;
} ebMACFONT, ebFAR *ebLPMACFONT;

#define ebHAVE_OLE				/* this platform supports OLE 2.0 automation */
typedef RGBColor ebCOLOR;
typedef long ebHCURSOR;
#define ebMSG ebUINT
#define ebWPARAM unsigned int
#define ebLPARAM long
#define ebLRESULT long
#define ebMAKELONG(a,b) ((ebLONG)(((ebWORD)(a))|((ebDWORD)((ebWORD)(b)))<<16))
#define ebMAKELPARAM(a,b) ((ebLPARAM)ebMAKELONG((a),(b)))

#endif	/* EBMAC */

#ifdef WANT_PACK
/* if we want packing, then make it on a byte boundary */
#pragma pack(1)
#endif	/* WANT_PACK */

ebDECLARE_HANDLE(ebHSUB);
typedef ebHSUB ebFAR *ebLPHSUB;

/*
 *	To make C calling conventions compatible over all Macintosh compilers,
 *	all integer and character parameters must be declared as 32-bit quantities.
 *	_ebWORD and _ebHSUB are declared for this use.
 *
 *	In structures, to be cross platform compatible, these types must be
 *	16-bit quantities.
 *
 *	On non-Macintosh platforms, these types are the same.
 */
typedef unsigned short ebWORD;	/* 16 bit unsigned integer */

#if defined(EBMAC) && !defined(powerc) && !defined(__powerc)
#ifndef __TYPES__
#include <Types.h>
#endif	/* !__TYPES__ */

typedef unsigned long _ebWORD;	/* 32 bit unsigned integer for argument passing  */
typedef unsigned long _ebHSUB;	/* 32 bit unsigned integer for argument passing */
typedef long _short;					/* 32 bit unsigned integer for argument passing */
typedef long _ebBOOL;				/* 32 bit unsigned integer for argument passing */
typedef extended80 _double;		/* 80 bit SANE type for argument passing */
typedef extended80 _float;			/* 80 bit SANE type for argument passing */
#else	/* !EBMAC */
typedef ebWORD _ebWORD;				/* 16 bit unsigned integer */
typedef ebHSUB _ebHSUB;
typedef short _short;
typedef short _ebBOOL;
typedef double _double;
typedef float _float;
#endif /* !EBMAC */
#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Resource compiler fixes
 * ----------------------------------------------------------------------- */
#ifdef RC_INVOKED
#define ebTEXT(s) s
#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Generic definitions used in all platforms
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED
typedef short ebBOOL;				/* integer 0 or 1 */
typedef char ebFAR *ebLPSTR;			/* 32 bit pointer to character */
#ifdef EBMAINWIN
typedef WCHAR ebWCHAR;
#else /* !EBMAINWIN */
typedef unsigned short ebWCHAR;	/* wide character */
#endif /* EBMAINWIN */

#ifdef EBWIDE
typedef ebWCHAR ebTCHAR;			/* single- or double-byte character */
#define ebTEXT(s) L##s				/* surrounds all string/character literals */
#else
typedef char ebTCHAR;				/* single- or double-byte character */
#define ebTEXT(s) s		  			/* surrounds all string/character literals */
#endif	/* !EBWIDE */

#ifdef EB64BIT
/*
 * On some platforms, longs are 64-bits. The BasicScript APIs require
 * that ebDWORD and ebLONG be 32-bits. Thus, these must be defined as ints.
 */
typedef unsigned int ebDWORD;				/* 32 bit unsigned integer */
typedef int ebLONG;							/* 32 bit signed integer */
typedef unsigned int ebFAR *ebLPDWORD;	/* 32 bit pointer to unsigned 32 bit integer */
#else	/* !EB64BIT */
typedef unsigned long ebDWORD;			/* 32 bit unsigned integer */
typedef long ebLONG;							/* 32 bit signed integer */
typedef unsigned long ebFAR *ebLPDWORD;	/* 32 bit pointer to unsigned 32 bit integer */
#endif	/* !EB64BIT */

typedef unsigned short ebFAR *ebLPWORD;	/* 32 bit pointer to unsigned integer */
typedef void ebFAR *ebLPVOID;				/* 32 bit pointer to void */
typedef const void ebFAR *ebLPCVOID;		/* 32 bit pointer to void */
typedef unsigned char ebBYTE;				/* 8 bit unsigned character */
typedef int ebFAR *ebLPINT;					/* 32-bit pointer to integer */
typedef const char ebFAR *ebLPCSTR;		/* 32-bit pointer to const character */
typedef ebLPVOID ebFAR *ebLPLPVOID;		/* pointer to array of pointers */
typedef ebTCHAR ebFAR *ebLPTSTR;			/* pointer to a BasicScript string */
typedef const ebTCHAR ebFAR *ebLPCTSTR;	/* constant pointer to a BasicScript string */
typedef ebTCHAR *ebPTSTR;					/* pointer to a BasicScript string */
typedef const ebTCHAR *ebPCTSTR;			/* constant pointer to a BasicScript string */
typedef ebWCHAR ebFAR *ebLPWSTR;			/* pointer to a BasicScript string */
typedef const ebWCHAR ebFAR *ebLPCWSTR;	/* constant pointer to a BasicScript string */
typedef ebWCHAR *ebPWSTR;					/* pointer to a BasicScript string */
typedef const ebWCHAR *ebPCWSTR;			/* constant pointer to a BasicScript string */
typedef ebBYTE ebFAR *ebLPBYTE;				/* 32-bit pointer to a byte */

#define ebDECLARE_HANDLE32(name)	struct name##__ { int unused; }; \
					typedef struct name##__ ebFAR* name

#define ebLOBYTE(w)			((unsigned char)(w))
#define ebHIBYTE(w)			((unsigned char)(((unsigned short)(w) >> 8) & 0xFF))
#define ebLOWORD(l)		 	((unsigned short)(ebDWORD)(l))
#define ebHIWORD(l)		 	((unsigned short)((((ebDWORD)(l)) >> 16) & 0xFFFF))
#define ebMAKEWORD(l,h)		((ebWORD)(((h) << 8) | (l)))
#define ebMAKEDWORD(l,h) 	((ebDWORD)(((h) << 16) | (l)))

#ifdef EBMAC
ebDECLARE_HANDLE32(ebHWND);
#endif /* EBMAC */

#endif	/* !RC_INVOKED */

/* define these until the APIs change */
#define ebLPXSTR ebLPTSTR
#define ebLPCXSTR ebLPCTSTR

/* --------------------------------------------------------------------------
 * If the OLE 2.0 header files have not yet been included, then define
 * ebLPDISPATCH as an ebLPVOID so that everything compiles without errors.
 * Otherwise, define it simply as LPDISPATCH. If the OLE include files
 * appear before this include file, then all is well. To make your code
 * compile correctly, include any OLE includes before including this
 * header file.
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED
#if !defined(_DISPATCH_H_) && !defined(_OLEAUTO_H_)
#define ebLPDISPATCH ebLPVOID		/* define these so stuff compiles */
#define ebLPTYPELIB ebLPVOID
#define ebLPTYPEINFO ebLPVOID
#define ebLCID ebDWORD
#ifdef EBMAC
#define LCID ebLCID
#endif /* EBMAC */
#else
#ifdef EBMAC
#define LCID ebDWORD
#endif /* EBMAC */
typedef LPDISPATCH ebLPDISPATCH;	/* these are the desired definitions */
typedef LPTYPELIB ebLPTYPELIB;
typedef LPTYPEINFO ebLPTYPEINFO;
typedef LCID ebLCID;
#endif
#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * BasicScript objects
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED
ebDECLARE_HANDLE32(ebHINSTANCE);		/* 32-bit ID used for to identify the app to the BasicScript system */
ebDECLARE_HANDLE32(ebHSCRIPT);		/* BasicScript script - many of these per module */
ebDECLARE_HANDLE32(ebHTHREAD);		/* BasicScript execution thread - many of these per module */
ebDECLARE_HANDLE32(ebHCODE);			/* BasicScript code */
#define ebHOBJECT ebLPCVOID			/* generic BasicScript object */

/* (T)hread (S)tates */
#define TS_IDLE						0	/* ready to run */
#define TS_RUNNING					1	/* currently running */
#define TS_SUSPENDED					2	/* suspended */

#define LO_CALLREQUESTORAFTER		0x00000001L	/* calls requestor after possible internal resolution */
#define LO_CALLREQUESTORBEFORE	0x00000002L	/* calls requestor before possible internal resolution */
#define LO_SEARCHSCRIPTS			0x00000004L	/* search created scripts for internal resolution */

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * (I)nstance (M)essage
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

#define ebIM_SETPUBLICSPACE				0		/* initializes the global space */
#define ebIM_SETREQUESTOR					1		/* sets the requestor routine use to request modules for forward referencing */
#define ebIM_SETRUNTIMEERRORPROC  		2		/* sets the error routine for the runtime */
#define ebIM_SETCOMMANDLINE				3		/* sets the command line for all threads, unless overridden by ebTM_SETCOMMANDLINE */
#define ebIM_SETOSVALUE						4		/* set the control knowledge routine */
#define ebIM_LOADPROCESSDATA				5		/* load the process data as part of the instance rather than part of an execution */
#define ebIM_GETOSVALUE						6		/* gets an OS-specific value */
#define ebIM_SETCOMPILERERRORPROC		7		/* sets the error routine for the compiler */
#define ebIM_GETCOMPILERERRORPROC		8		/* gets the compiler error routine and pass-through data */
#define ebIM_GETRUNTIMEERRORPROC			9		/* gets the runtime error routine and pass-through data */
#define ebIM_SETPCODECALLBACKPROC		10		/* sets the pcode callback routine */
#define ebIM_GETPCODECALLBACKPROC		11		/* gets the pcode callback routine */
#define ebIM_RESERVED						12		/* reserved message */
#define ebIM_GETCOUNTRY						13		/* grabs country information used by the runtime for this instance */
#define ebIM_SETCOUNTRY						14		/* sets the country information used by the runtime for this instance */
#define ebIM_SETPRINTPROC					15		/* sets the routine to call with the PRINT statement */
#define ebIM_GETPRINTPROC					16		/* gets the routine that is called by the PRINT statement */
#define ebIM_SETHOMEDIR						17		/* sets the home directory */
#define ebIM_RESETPUBLICS					18		/* resets the public data space */
#define ebIM_SETLINKOPTIONS				19		/* sets linker options */
#define ebIM_SETTHIS							20		/* sets the 'this' pointer */
#define ebIM_GETTHIS							21		/* gets the 'this' pointer */
#define ebIM_SETRUNTIMELOADSTRINGPROC	22		/* sets routine to call for runtime strings */
#define ebIM_SETCOMPILERLOADSTRINGPROC	23		/* sets routine to call for compiler strings */
#define ebIM_SETLONG							24		/* sets a long value in the instance-extra bytes */
#define ebIM_GETLONG							25		/* gets a long value in the instance-extra bytes */
#define ebIM_SETWORD							26		/* sets a word value in the instance-extra bytes */
#define ebIM_GETWORD							27		/* gets a word value in the instance-extra bytes */
#define ebIM_SETNAME							28		/* sets the name of the application */
#define ebIM_SETFONT							29		/* sets the font for the BasicScript runtime (overriding the default in runtime resource) */
#define ebIM_GETNAME							30		/* gets the name of the application */
#define ebIM_SETNATIVETOPORTABLEPROC	31		/* sets the routine that converts native to portable strings */
#define ebIM_SETPORTABLETONATIVEPROC	32		/* sets the routine that converts portable to native strings */
#define ebIM_SETYIELDFREQUENCY			33		/* sets the frequency which the application's pcode callback routine is called */
#define ebIM_SETSQLSYNCREQUESTS			36		/* sets the behavior of the SQL serialization code */

#if defined(EBMAC) && HAVE_ANYDIALOGS
#define ebIM_SETEVENTHANDLER2				34		/* for Mac when wrappers used; sets the event handler for callback purposes  */
#define ebIM_SETDLGPROC						35		/* sets the dialog procedure */

#ifdef NEWMACDBGR
#define ebInstance_IsEvent(hInst,eventPtr) (ebBOOL)ebSendMessage(hInst,ebIM_SETOSVALUE,(ebPARAM1)16,(ebPARAM2)(eventPtr))
#define ebInstance_DoEvent(hInst,eventPtr) (void)ebSendMessage(hInst,ebIM_SETOSVALUE,(ebPARAM1)17 ,(ebPARAM2)(eventPtr))
#endif

/*ebBOOL ebAPI ebDebugger_IsEvent(ebHWND hWnd,const EventRecord *anEvent);

void ebAPI ebDebugger_DoEvent(ebHWND hWnd,const EventRecord *anEvent); */

/* ebMACEVENTHANDLER ebInstance_SetEventHandler(ebHINSTANCE hInst,ebMACEVENTHANDLER lpfnHandler); */
#define ebInstance_SetEventHandler(hInst,lpfnHandler) (ebMACEVENTHANDLER)ebSendMessage(hInst,ebIM_SETOSVALUE,(ebPARAM1)1,(ebPARAM2)(ebMACEVENTHANDLER)(lpfnHandler))

/* ebMACEVENTHANDLER2 ebInstance_SetEventHandler2(ebHINSTANCE hInst, long lParam, ebMACEVENTHANDLER2 lpfnHandler); */
#define ebInstance_SetEventHandler2(hInst,lParam, lpfnHandler) (ebMACEVENTHANDLER2)ebSendMessage(hInst,ebIM_SETEVENTHANDLER2,(ebPARAM1)(lParam),(ebPARAM2)(ebMACEVENTHANDLER2)(lpfnHandler))

/* void ebInstance_SetDlgProc(ebHINSTANCE hInst,ebLONG lParam,ebDLGPROC lpfnDlgProc); */
#define ebInstance_SetDlgProc(hInst,lParam,lpfnDlgProc) ebSendMessage(hInst,ebIM_SETDLGPROC,(ebPARAM1)(lParam),(ebPARAM2)(ebDLGPROC)(lpfnDlgProc))
#endif /* defined(EBMAC) && HAVE_ANYDIALOGS */

/* ebWORD ebInstance_SetYieldFrequency(ebHINSTANCE hInst,ebWORD wNewFrequency); */
#define ebInstance_SetYieldFrequency(hInst,wNewFrequency) (ebWORD)ebSendMessage(hInst,ebIM_SETYIELDFREQUENCY,(ebPARAM2)(ebDWORD)(ebWORD)(wNewFrequency),0)

/* ebBOOL ebInstance_SetSqlSyncRequests(ebHINSTANCE hInst,_ebBOOL bSyncRequests); */
#define ebInstance_SetSqlSyncRequests(hInst,bSyncRequests) (ebBOOL)ebSendMessage(hInst,ebIM_SETSQLSYNCREQUESTS,(ebPARAM2)(ebDWORD)(_ebBOOL)(bSyncRequests),0)

/* ebDWORD ebInstance_SetMaxOleObjects(ebHINSTANCE hInst,ebDWORD dwNewNumObjects); */
#define ebInstance_SetMaxOleObjects(hInst,dwNewNumObjects) (ebDWORD)ebSendMessage(hInst,ebIM_SETOSVALUE,4,(ebPARAM2)(ebDWORD)(dwNewNumObjects))

/* int ebInstance_CallMathErr(ebHINSTANCE hInst,ebLPVOID pException); */
#ifdef EBMAINWIN
#define ebInstance_CallMathErr(hInst,pException) (int)ebSendMessage(hInst,ebIM_SETOSVALUE,17,(ebPARAM2)(ebLPVOID)(pException))
#else
#define ebInstance_CallMathErr(hInst,pException) (int)ebSendMessage(hInst,ebIM_SETOSVALUE,3,(ebPARAM2)(ebLPVOID)(pException))
#endif

/* ebDWORD ebInstance_SetMaxConstOleObjects(ebHINSTANCE hInst,ebDWORD dwNewNumObjects); */
#define ebInstance_SetMaxConstOleObjects(hInst,dwNewNumObjects) (ebDWORD)ebSendMessage(hInst,ebIM_SETOSVALUE,5,(ebPARAM2)(ebDWORD)(dwNewNumObjects))

/* ebBOOL ebInstance_SetSingleThreaded(ebHINSTANCE hInst,_ebBOOL isSingleThreaded); */
#define ebInstance_SetSingleThreaded(hInst,isSingleThreaded) (ebBOOL)ebSendMessage(hInst,ebIM_SETOSVALUE,6,(ebPARAM2)(ebDWORD)(isSingleThreaded))

/* ebLPTSTR ebFAR *ebInstance_SetEnvironment(ebHINSTANCE hInst,ebLPTSTR ebFAR *lpEnvironment); */
#define ebInstance_SetEnvironment(hInst,lpEnvironment) (ebLPTSTR ebFAR *)ebSendMessage(hInst,ebIM_SETOSVALUE,7,(ebPARAM2)(ebLPTSTR)(lpEnvironment))

/* void ebInstance_GetName(ebHINSTANCE hInst,ebLPTSTR lpDest,ebINT iMaxLen); */
#define ebInstance_GetName(hInst,lpDest,iMaxLen) ebSendMessage(hInst,ebIM_GETNAME,(ebPARAM1)(iMaxLen),(ebPARAM2)(ebLPTSTR)(lpDest))

/* void ebInstance_SetFont(ebHINSTANCE hInst,ebLPCTSTR lpFontSpec); */
#define ebInstance_SetFont(hInst,lpFontSpec) ebSendMessage(hInst,ebIM_SETFONT,(ebPARAM1)0,(ebPARAM2)(lpFontSpec))

/* void ebInstance_SetNativeToPortableProc(ebHINSTANCE hInst,long lParam,ebNATIVETOPORTABLEPROC lpfnNativeToPortable); */
#define ebInstance_SetNativeToPortableProc(hInst,lParam,lpfnNativeToPortable) ebSendMessage(hInst,ebIM_SETNATIVETOPORTABLEPROC,(ebPARAM1)(lParam),(ebPARAM2)(ebNATIVETOPORTABLEPROC)(lpfnNativeToPortable))

/* void ebInstance_SetPortableToNativeProc(ebHINSTANCE hInst,long lParam,ebPORTABLETONATIVEPROC lpfnPortableToNative); */
#define ebInstance_SetPortableToNativeProc(hInst,lParam,lpfnPortableToNative) ebSendMessage(hInst,ebIM_SETPORTABLETONATIVEPROC,(ebPARAM1)(lParam),(ebPARAM2)(ebPORTABLETONATIVEPROC)(lpfnPortableToNative))

/* void ebInstance_GetCompilerErrorProc(ebHINSTANCE hInst,long ebFAR *lplParam,ebERRORPROC ebFAR *lplpfnError); */
#define ebInstance_GetCompilerErrorProc(hInst,lplParam,lplpfnError) ebSendMessage(hInst,ebIM_GETCOMPILERERRORPROC,(ebPARAM1)(lplParam),(ebPARAM2)(ebERRORPROC ebFAR *)(lplpfnError))

/* void ebInstance_SetRuntimeLoadStringProc(ebHINSTANCE hInst,long lParam,ebLOADSTRINGPROC lpfnLoadStringProc); */
#define ebInstance_SetRuntimeLoadStringProc(hInst,lParam,lpfnLoadStringProc) ebSendMessage(hInst,ebIM_SETRUNTIMELOADSTRINGPROC,(ebPARAM1)(lParam),(ebPARAM2)(ebLOADSTRINGPROC)(lpfnLoadStringProc))

/* void ebInstance_SetCompilerLoadStringProc(ebHINSTANCE hInst,long lParam,ebLOADSTRINGPROC lpfnLoadStringProc); */
#define ebInstance_SetCompilerLoadStringProc(hInst,lParam,lpfnLoadStringProc) ebSendMessage(hInst,ebIM_SETCOMPILERLOADSTRINGPROC,(ebPARAM1)(lParam),(ebPARAM2)(ebLOADSTRINGPROC)(lpfnLoadStringProc))

/* void ebInstance_GetCountry(ebHINSTANCE hInst,ebLPCOUNTRY lpCountry); */
#define ebInstance_GetCountry(hInst,lpCountry) ebSendMessage(hInst,ebIM_GETCOUNTRY,(ebPARAM1)0,(ebPARAM2)(ebLPSTR)(lpCountry))

/* ebHWND ebInstance_GetWindow(ebHINSTANCE hInst); */
#define ebInstance_GetWindow(hInst) (ebHWND)ebSendMessage(hInst,ebIM_GETOSVALUE,(ebPARAM1)0,(ebPARAM2)0)

/* ebCKPROC ebInstance_GetCKProc(ebHINSTANCE hInst); */
#define ebInstance_GetCKProc(hInst) (ebCKPROC)ebSendMessage(hInst,ebIM_GETOSVALUE,(ebPARAM1)1,(ebPARAM2)0)

/* ebMACEVENTHANDLER ebInstance_GetEventHandler(hInst); */
#define ebInstance_GetEventHandler(hInst) (ebMACEVENTHANDLER)ebSendMessage(hInst,ebIM_GETOSVALUE,(ebPARAM1)0,(ebPARAM2)0)

/* void ebInstance_GetPcodeCallbackProc(ebHINSTANCE hInst,long ebFAR *lplParam,ebPCODECALLBACKPROC ebFAR *lplpfnPcodeCallbackProc); */
#define ebInstance_GetPcodeCallbackProc(hInst,lplParam,lplpfnPcodeCallbackProc) ebSendMessage(hInst,ebIM_GETPCODECALLBACKPROC,(ebPARAM1)(lplParam),(ebPARAM2)(ebPCODECALLBACKPROC ebFAR *)(lplpfnPcodeCallbackProc))

/* void ebInstance_GetPrintProc(ebHINSTANCE hInst,long ebFAR *lplParam,ebPRINTPROC ebFAR *lplpfnPrintProc); */
#define ebInstance_GetPrintProc(hInst,lplParam,lplpfnPrintProc) ebSendMessage(hInst,ebIM_GETPRINTPROC,(ebPARAM1)(lplParam),(ebPARAM2)(ebPRINTPROC ebFAR *)(lplpfnPrintProc))

/* void ebInstance_GetRuntimeErrorProc(ebHINSTANCE hInst,long ebFAR *lplParam,ebERRORPROC ebFAR *lplpfnError); */
#define ebInstance_GetRuntimeErrorProc(hInst,lplParam,lplpfnError) ebSendMessage(hInst,ebIM_GETRUNTIMEERRORPROC,(ebPARAM1)(lplParam),(ebPARAM1)(ebERRORPROC ebFAR *)(lplpfnError))

/* ebBOOL ebInstance_LoadProcessData(ebHINSTANCE hInst); */
#define ebInstance_LoadProcessData(hInst) (ebBOOL)ebSendMessage(hInst,ebIM_LOADPROCESSDATA,(ebPARAM1)0,(ebPARAM2)0)

/* ebINT ebInstance_ResetPublics(ebHINSTANCE hInst); */
#define ebInstance_ResetPublics(hInst) (ebINT)ebSendMessage(hInst,ebIM_RESETPUBLICS,(ebPARAM1)0,(ebPARAM2)0)

/* void ebInstance_SetCommandLine(ebHINSTANCE hInst,ebLPCTSTR lpNewCmdLine); */
#define ebInstance_SetCommandLine(hInst,lpNewCmdLine) ebSendMessage(hInst,ebIM_SETCOMMANDLINE,(ebPARAM1)0,(ebPARAM2)(ebLPCTSTR)(lpNewCmdLine))

/* void ebInstance_SetCompilerErrorProc(ebHINSTANCE hInst,long lParam,ebERRORPROC lpfnError); */
#define ebInstance_SetCompilerErrorProc(hInst,lParam,lpfnError) ebSendMessage(hInst,ebIM_SETCOMPILERERRORPROC,(ebPARAM1)(lParam),(ebPARAM2)(ebERRORPROC)(lpfnError))

/* ebBOOL ebInstance_SetCountry(ebHINSTANCE hInst,ebLPCOUNTRY lpCountry); */
#define ebInstance_SetCountry(hInst,lpCountry) (ebBOOL)ebSendMessage(hInst,ebIM_SETCOUNTRY,(ebPARAM1)0,(ebPARAM2)(ebLPCOUNTRY)(lpCountry))

/* void ebInstance_SetHomeDir(ebHINSTANCE hInst,ebLPCTSTR lpDir); */
#define ebInstance_SetHomeDir(hInst,lpDir) ebSendMessage(hInst,ebIM_SETHOMEDIR,(ebPARAM1)0,(ebPARAM2)(ebLPCTSTR)(lpDir))

/* ebDWORD ebInstance_SetLinkOptions(ebHINSTANCE hInst,ebDWORD dwLinkOptions); */
#define ebInstance_SetLinkOptions(hInst,dwLinkOptions) (ebDWORD)ebSendMessage(hInst,ebIM_SETLINKOPTIONS,(ebPARAM1)(ebDWORD)(dwLinkOptions),(ebPARAM2)0)

/* ebHWND ebInstance_SetWindow(ebHINSTANCE hInst,ebHWND hWnd); */
#ifdef EBMAINWIN
#define ebInstance_SetWindow(hInst,hWnd) (ebHWND)ebSendMessage(hInst,ebIM_SETOSVALUE,(ebPARAM1)0,sizeof(ebHWND) == 2 ? (ebPARAM2)(hWnd) : (ebPARAM2)(hWnd))
#else
#define ebInstance_SetWindow(hInst,hWnd) (ebHWND)ebSendMessage(hInst,ebIM_SETOSVALUE,(ebPARAM1)0,sizeof(ebHWND) == 2 ? (ebPARAM2)ebMAKELONG((hWnd),0) : (ebPARAM2)(hWnd))
#endif

/* ebHWND ebInstance_SetViewportParent(ebHINSTANCE hInst,ebHWND hWnd); */
#define ebInstance_SetViewportParent(hInst,hWnd) (ebHWND)ebSendMessage(hInst,ebIM_SETOSVALUE,(ebPARAM1)8,sizeof(ebHWND) == 2 ? (ebPARAM2)ebMAKELONG((hWnd),0) : (ebPARAM2)(hWnd))

/* void ebInstance_SetLCID(ebHINSTANCE hInst,ebLCID lcid); */
#define ebInstance_SetLCID(hInst,lcid) ebSendMessage(hInst,ebIM_SETOSVALUE,(ebPARAM1)3,(ebPARAM2)lcid)

/* ebLCID ebInstance_GetLCID(ebHINSTANCE hInst); */
#define ebInstance_GetLCID(hInst,lcid) ebSendMessage(hInst,ebIM_GETOSVALUE,(ebPARAM1)3,0)

/* ebHWND ebInstance_SetWidgetParent(ebHINSTANCE hInst,Widget parent); */
#define ebInstance_SetWidgetParent(hInst,parent) (ebLPVOID)ebSendMessage(hInst,ebIM_SETOSVALUE,(ebPARAM1)0,(ebPARAM2)parent)

typedef int (ebCALLBACK _ebXMESSAGELOOPPROC)(void);
typedef _ebXMESSAGELOOPPROC *ebXMESSAGELOOPPROC;

/* void ebInstance_SetXMessageLoopProc(ebHINSTANCE hInst,ebXMESSAGELOOPPROC lpfnProc); */
#define ebInstance_SetXMessageLoopProc(hInst,lpfnProc) (ebLPVOID)ebSendMessage(hInst,ebIM_SETOSVALUE,(ebPARAM1)1,(ebPARAM2)lpfnProc)

/* void ebInstance_RemoveXMessageLoopProc(ebHINSTANCE hInst); */
#define ebInstance_RemoveXMessageLoopProc(hInst) (ebLPVOID)ebSendMessage(hInst,ebIM_SETOSVALUE,(ebPARAM1)2,(ebPARAM2)NULL)

#define ebICON_EXCLAMATION		0	/* icon IDs for UNIX platforms, used by ebInstance_SetIconData */
#define ebICON_INFORMATION		1
#define ebICON_QUESTION			2
#define ebICON_STOP				3

/* void ebInstance_SetIconData(ebHINSTANCE hInst,int index,char **lpData); */
#define ebInstance_SetIconData(hInst,index,lpData) (ebLPVOID)ebSendMessage(hInst,ebIM_SETOSVALUE,(ebPARAM1)(10 + (index)),(ebPARAM2)(lpData))

/* ebCKPROC ebInstance_SetCKProc(ebHINSTANCE hInst,ebCKPROC lpfnCKProc); */
#define ebInstance_SetCKProc(hInst,lpfnCKProc) (ebCKPROC)ebSendMessage(hInst,ebIM_SETOSVALUE,(ebPARAM1)1,(ebPARAM2)(ebCKPROC)(lpfnCKProc))

/* void ebInstance_SetPcodeCallbackProc(ebHINSTANCE hInst,long lParam,ebPCODECALLBACKPROC lpfnPcodeCallbackProc); */
#define ebInstance_SetPcodeCallbackProc(hInst,lParam,lpfnPcodeCallbackProc) ebSendMessage(hInst,ebIM_SETPCODECALLBACKPROC,(ebPARAM1)(lParam),(ebPARAM2)(ebPCODECALLBACKPROC)(lpfnPcodeCallbackProc))

/* void ebInstance_SetPrintProc(ebHINSTANCE hInst,long lParam,ebPRINTPROC lpfnPrintProc); */
#define ebInstance_SetPrintProc(hInst,lParam,lpfnPrintProc) ebSendMessage(hInst,ebIM_SETPRINTPROC,(ebPARAM1)(ebLONG)(lParam),(ebPARAM2)(ebPRINTPROC)(lpfnPrintProc))

/* ebBOOL ebInstance_SetPublicSpace(ebHINSTANCE hInst,ebDWORD dwNewSize); */
#define ebInstance_SetPublicSpace(hInst,dwNewSize) (ebBOOL)ebSendMessage(hInst,ebIM_SETPUBLICSPACE,(ebPARAM1)(ebDWORD)(dwNewSize),(ebPARAM2)0)

/* void ebInstance_SetRequestor(ebHINSTANCE hInst,long lParam,ebREQUESTORPROC lpfnRequestor); */
#define ebInstance_SetRequestor(hInst,lParam,lpfnRequestor) ebSendMessage(hInst,ebIM_SETREQUESTOR,(ebPARAM1)(ebLONG)(lParam),(ebPARAM2)(ebREQUESTORPROC)(lpfnRequestor))

/* void ebInstance_SetRuntimeErrorProc(ebHINSTANCE hInst,long lParam,ebERRORPROC lpfnError); */
#define ebInstance_SetRuntimeErrorProc(hInst,lParam,lpfnError) ebSendMessage(hInst,ebIM_SETRUNTIMEERRORPROC,(ebPARAM1)(lParam),(ebPARAM2)(ebERRORPROC)(lpfnError))

/* void ebInstance_SetThis(ebHINSTANCE hInst,ebDWORD dwThis); */
#define ebInstance_SetThis(hInst,dwThis) ebSendMessage(hInst,ebIM_SETTHIS,(ebPARAM1)(ebDWORD)(dwThis),(ebPARAM2)0)

/* ebDWORD ebInstance_GetThis(ebHINSTANCE hInst); */
#define ebInstance_GetThis(hInst) (ebDWORD)ebSendMessage(hInst,ebIM_GETTHIS,(ebPARAM1)0,(ebPARAM2)0)

/* void ebInstance_SetLong(ebHINSTANCE hInst,ebDWORD dwOffset,long lValue); */
#define ebInstance_SetLong(hInst,dwOffset,lValue) ebSendMessage(hInst,ebIM_SETLONG,(ebPARAM1)(ebDWORD)(dwOffset),(ebPARAM2)(long)(lValue))

/* long ebInstance_GetLong(ebHINSTANCE hInst,ebDWORD dwOffset); */
#define ebInstance_GetLong(hInst,dwOffset) (long)ebSendMessage(hInst,ebIM_GETLONG,(ebPARAM1)(ebDWORD)(dwOffset),(ebPARAM2)0)

/* ebWORD ebInstance_GetWord(ebHINSTANCE hInst,ebDWORD dwOffset); */
#define ebInstance_GetWord(hInst,dwOffset) (ebWORD)ebSendMessage(hInst,ebIM_GETWORD,(ebPARAM1)(ebDWORD)(dwOffset),(ebPARAM2)0)

/* void ebInstance_SetWord(ebHINSTANCE hInst,ebDWORD dwOffset,_ebWORD wValue); */
#define ebInstance_SetWord(hInst,dwOffset,wValue) ebSendMessage(hInst,ebIM_SETWORD,(ebPARAM1)(ebDWORD)(dwOffset),(ebPARAM2)(_ebWORD)(wValue))

/* void ebInstance_SetName(ebHINSTANCE hInst,ebLPCTSTR lpName); */
#define ebInstance_SetName(hInst,lpName) ebSendMessage(hInst,ebIM_SETNAME,(ebPARAM1)0,(ebPARAM2)(ebLPCTSTR)(lpName))

#define ebPARENT_MESSAGE	 		2	/* Msg.Open method */
#define ebPARENT_USERDIALOG 		3	/* Dialog statement/function */
#define ebPARENT_SHELL		  		4	/* Shell function */
#define ebPARENT_NETBROWSE			5	/* Net.Browse method */
#define ebPARENT_NETDIALOG			6	/* Net.Dialog method */
#define ebPARENT_ASK		 			7	/* AskBox function */
#define ebPARENT_ANSWER	 			8	/* AnswerBox function */
#define ebPARENT_OPENFILENAME		9	/* OpenFileName$ function */
#define ebPARENT_SELECTBOX			10	/* SelectBox function */
#define ebPARENT_SAVEFILENAME		11	/* SaveFileName$ function */
#define ebPARENT_INPUTBOX	  		12	/* InputBox[$] function */
#define ebPARENT_MSGBOX	   		13	/* MsgBox statement/function */
#define ebPARENT_SQLCONNECT   	14	/* SQLConnect statement */
#define ebPARENT_CLIPBOARD			15	/* Clipboard.Open statement */
#define ebPARENT_IMESTATUS			16	/* IMEStatus function */
#define ebPARENT_POPUPMENU			17	/* PopupMenu function */

typedef ebHWND (ebCALLBACK _ebPARENTGETPROC)(ebHTHREAD hThread,int place);
typedef _ebPARENTGETPROC *ebPARENTGETPROC;

/* ebPARENTGETPROC ebInstance_SetParentGetProc(ebHINSTANCE hInst,ebPARENTGETPROC lpfnParentGet); */
#define ebInstance_SetParentGetProc(hInst,lpfnParentGet) ebSendMessage((hInst),ebIM_SETOSVALUE,(ebPARAM1)9,(ebPARAM2)(lpfnParentGet))

#ifdef EBJAVA
#include <jni.h>

typedef jint ebJINT;
typedef struct _ebJVMINITARGS* ebPJVMINITARGS;
typedef ebBOOL (ebCREATEJVMFUNC)(ebPJVMINITARGS pJVMInitArgs, JavaVM** ppJVM,
							  JNIEnv** ppEnv, ebLPVOID lpThreadRef);
typedef ebCREATEJVMFUNC* ebPCREATEJVMFUNC;

typedef void (ebJVMCREATEDFUNC)(ebPJVMINITARGS pJVMInitArgs, ebBOOL bSucceeded);
typedef ebJVMCREATEDFUNC* ebPJVMCREATEDFUNC;

/* 
 * This pointer to ebJVMInitArgs structure is saved.  It performs no copying
 * of the data, hence all memory reference by this structure must be valid
 * at the time of the first call to a Java object.  In most cases, this
 * can be achieved with a global variable.  Alternatively, the application
 * may allocate the structure and pass a callback to the initialization 
 * structure via lpfnJVMCreated member.  If set, the engine will call
 * this function upon attempting to create the Java VM passing in a 
 * pointer to the ebJVMINITARGS structure and a boolean indicating
 * whether the call to initialize the VM succeeded.  If the initialization
 * was allocated, the application can free the memory as appropriate.
 */
/* ebBOOL ebInstance_SetJavaInitArgs(ebHINSTANCE hInst, ebPJVMINITARGS pJVMInitArgs); */
#define ebInstance_SetJavaInitArgs(hInst,pJVMInitArgs) (ebBOOL)ebSendMessage(hInst,ebIM_SETOSVALUE,19,(ebPARAM2)(ebPJVMINITARGS)(pJVMInitArgs))

/* 
 * Function pointer for CreateJavaVM.
 * The application can provide their own CreateJavaVM function for special
 * initialization of the Java VM.  This function should return 1 on
 * success; 0 on failure.  Note that this this differs from the JNI
 * convention where success is indicated by 0 and failure by a negative
 * return value.  The references to the Java VM and Java environment
 * are returned via the parameters ppJVM and ppEnv respectively.  These
 * should be set to NULL in the event of failure.  
 */

#define ebJNIVersion1_1		0x00010001
#define ebJNIVersion1_2		0x00010002

/*
 * Structure for passing Java environment information to 
 * BasicScript.  Note that alpszProperties is an array
 * of char*, not TCHAR*.  All unused members should be set 
 * to NULL;
 */
typedef struct _ebJVMINITARGS
{
	/* This allows the aplication to specify a specialized routine
	 * for initializing the Java VM.  In most cases, it will not
	 * be necessary to provide such a method and this member should 
	 * be set to NULL.  The other member variables provide a 
	 * mechanism for specifying the setup environment. Note that 
	 * if you set this member, all other members in this structure 
	 * are ignored.  The lpfnCreateJVM method is passed a reference to this
	 * structure so a specialized routine may use it for its own 
	 * purposes. */
	ebPCREATEJVMFUNC	lpfnCreateJVM;


	/* Path to the Java dynamically linked library (javai.dll/so 
	 * or jvm.dll/so).  Note that the default class path is determined 
	 * relative to this location, so if you put a copy of the Java
	 * DLL in directory outside of the directory structure set up
	 * by the Java installation program, you may need to explicitly
	 * set the classpath variables. */
	ebLPCTSTR		lpszJavaLibPath;

	/* A pointer to a VM-specific initilization structure.  Use
	 * this member for finer grain control of how the VM is
	 * initialized.  If this member is set, the classpath and
	 * properties variables of this structure are ignored. 
	 * (However, the lpfnCreateJVM member takes precedence and 
	 * any library indicated by lpszJavaLibPath is loaded.)  
	 * Specifically, this is a pointer to either a JDK1_1InitArgs 
	 * structure (JDK 1.1) or JavaVMInitArgs structure (JDK 1.2).
	 */
	ebLPVOID		lpJVMDependentInitArgs;

	/* The version of the Java runtime.  If specified, this should
	 * be set to ebJNIVersion1_1 or ebJNIVersion1_2.  Otherwise,
	 * this should be set to NULL.  The default version of the 
	 * Java runtime is determined by the JDK version of included jni.h.
	 * If the application was built against the 1.2 version of jni.h,
	 * then the aplication defaults to 1.2.  Otherwise, 1.1 is used.
	 * A 1.2 version may specify ebJNIVersion1_1. */
	ebJINT				jintJNIVersion;

	/* TO DO: Add more explanation for the classpath variables.  
	 * See Spec for more details.  the effect of setting these 
	 * variables depends on the version of the Java runtime that
	 * you want to load. */

	/* The classpath for the system or bootstrap classes.
	 * (e.g. java.lang.*, java.io.*, etc.). */
	ebLPCTSTR			lpszBootstrapClasspath;

	/* The classpath for user (non-core) libraries. 
	 * JDK 1.2 makes a distinction between the bootstrap 
	 * classes and user library classes.  If you are 
	 * loading the 1.2 library, lpszUserClasspath will 
	 * replace the CLASSPATH environment variable but will
	 * NOT replace the bootstrap classpath.  For 1.1, it
	 * is advised that use lpszBootstrapClasspath and 
	 * lpszUserAppendClasspath, but not this variable. */
	ebLPCTSTR			lpszUserClasspath;

	/* If this variable is set it will append the specified
	 * classpath to the existing CLASSPATH (or the path 
	 * specified by lpszUserClasspath if that is set).  
	 * Use this variable, if want to keep whatever path is
	 * set by the CLASSPATH variable and you just want to
	 * append onto it. */
	ebLPCTSTR			lpszUserAppendClasspath;

	/* If you want to set System properties at startup, you may
	 * may do so through this member.  The alpszProperties
	 * array should take the following form:
	 * [prop_name1=prop_val1][prop_name2=prop_val2]...[prop_nameN=prop_valN][NULL]
	 * Note that this array should comprise multibyte strings.
	 * You may use this to set properties for both 1.1 and 1.2
	 * Java runtimes, but is recommended that for 1.2, you
	 * create your own JavaVMInitArgs structure and set
	 * lpJVMDependentInitArgs rather than use alpszProperties. */
	ebLPSTR*			alpszProperties;

	/* Optional callback that the application can supply to be notified 
	 * that the engine has attempted to create the Java VM.  A pointer
	 * to this initialization structure  and a boolean indicating 
	 * whether the VM creation was successful is passed to the callback. */
	ebPJVMCREATEDFUNC	lpfnJVMCreated;

	/* An application should set this flag if it is possible that it 
	 * created a Java VM on its own.  Currently, an application should
	 * not do this if it is running the BasicScript engine multithreaded. */
	ebBOOL				bCheckForCreatedVMs;

	/* Reserved for use by a specialized CreateJVM routine.  Such
	 * a routine may use this variable in any way it chooses. */
	ebLPVOID			lpSpecialArgs;

	/* Reserved */
	ebDWORD				dwReserved;

	/* An ASCII string identifying the encoding scheme to use for strings. */
	ebLPCSTR			lpszEncodingScheme;

	/* Reserved */
	ebLPVOID			lpReserved2;
} ebJVMINITARGS;

#endif /* EBJAVA */

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * (S)cript (M)essages
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

#define ebSM_GETINSTANCE				0		/* retrieves the instance owning the script */
#define ebSM_SETTHIS						1		/* sets the 'this' pointer */
#define ebSM_GETTHIS						2		/* gets the 'this' pointer */
#define ebSM_SETNAME						3		/* sets the name of the script */
#define ebSM_GETNAME						4		/* gets the name of the script */

/* ebHINSTANCE ebScript_GetInstance(ebHSCRIPT hScript); */
#define ebScript_GetInstance(hScript) (ebHINSTANCE)ebSendMessage(hScript,ebSM_GETINSTANCE,(ebPARAM1)0,(ebPARAM2)0)

/* void ebScript_SetThis(ebHSCRIPT hScript,ebDWORD dwThis); */
#define ebScript_SetThis(hScript,dwThis) ebSendMessage(hScript,ebSM_SETTHIS,(ebPARAM1)(ebDWORD)(dwThis),(ebPARAM2)0)

/* ebDWORD ebScript_GetThis(ebHSCRIPT hScript); */
#define ebScript_GetThis(hScript) (ebDWORD)ebSendMessage(hScript,ebSM_GETTHIS,(ebPARAM1)0,(ebPARAM2)0)

/* void ebScript_SetName(ebHSCRIPT hScript,ebLPCTSTR lpName); */
#define ebScript_SetName(hScript,lpName) ebSendMessage(hScript,ebSM_SETNAME,(ebPARAM1)0,(ebPARAM2)(ebLPCTSTR)(lpName))

/* void ebScript_GetName(ebHSCRIPT hScript,ebLPTSTR lpDest,ebINT iMaxLen); */
#define ebScript_GetName(hScript,lpDest,iMaxLen) ebSendMessage(hScript,ebSM_GETNAME,(ebPARAM1)(iMaxLen),(ebPARAM2)(ebLPTSTR)(lpDest))

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * (T)hread (M)essages
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

#define ebTM_SETCOMMANDLINE			0		/* sets the command line (overrides the INSTANCE command line for this execution) */
#define ebTM_GETERRORLINE				1		/* gets the line number of the error */
#define ebTM_GETERRORNUMBER			2		/* gets the error number if thread died dur to runtime error */
#define ebTM_GETSTATE					3		/* gets the state of a thread (running or suspended) */
#define ebTM_GETLONG						4		/* gets an app-specific LONG value from the thread */
#define ebTM_SETLONG						5		/* sets an app-specific LONG value in the thread */
#define ebTM_GETWORD						6		/* gets an app-specific WORD value from the thread */
#define ebTM_SETWORD						7		/* sets an app-specific WORD value in the thread */
#define ebTM_GETINSTANCE				8		/* gets the INSTANCE that owns the thread */
#define ebTM_SETSTACK					9		/* sets the stack size */
#define ebTM_ENABLEBREAK				10		/* enables Ctrl+Break checking during execution */
#define ebTM_INTERRUPT					11		/* interrupts an execution script, optionally terminating it */
#define ebTM_ISINTERRUPTED				12		/* returns TRUE if a script has been interrupted, FALSE otherwise */
#define ebTM_SETENTRYINFO				13		/* changes the entry point information used for this thread */
#define ebTM_SETHOMEDIR					14		/* sets the home directory */
#define ebTM_SETLINKOPTIONS			15		/* sets linker options */
#define ebTM_SETRUNTIMEERRORPROC  	16		/* sets the error routine for the runtime */
#define ebTM_SETPRINTPROC	 			17		/* sets the print routine for the runtime */
#define ebTM_GETSCRIPT					18		/* gets the script in use by this thread */
#define ebTM_GETOPTIONBASE				19		/* gets the current option base for executing threads */
#define ebTM_SETTHIS						20		/* sets the 'this' pointer */
#define ebTM_GETTHIS						21		/* gets the 'this' pointer */
#define ebTM_GETDIALOGCOUNT			22		/* return the number of displayed dialogs */
#define ebTM_SETSAVEDIR					23		/* gets and sets the isSaveDir setting of a thread */
#define ebTM_SETHELPPROC				24		/* registers a help callback */
#define ebTM_SETFONT						25		/* sets the font used by the BasicScript runtime (overriding that of the instance) */
#define ebTM_GETSTOPCONDITION			26		/* retrieves the reason for thread termination */
#define ebTM_GETRUNTIMEERRORPROC		27		/* retrieves the currently set runtime error procedure and data */
#define ebTM_GETCURRENTLINENUMBER			28		/* retrieves the current line number */
#define ebTM_GETLASTERRORLINE			29		/* retrieves the last error line number */
#define ebTM_SETENTRYEXITPROC			30	/* sets the proc executed when subs are entered and exited */

/* void ebThread_SetFont(ebHTHREAD hThread,ebLPCTSTR lpFontSpec); */
#define ebThread_SetFont(hThread,lpFontSpec) ebSendMessage(hThread,ebTM_SETFONT,(ebPARAM1)0,(ebPARAM2)(lpFontSpec))

/* ebBOOL ebThread_SetSaveDir(ebHTHREAD hThread,_ebBOOL isSaveDir); */
#define ebThread_SetSaveDir(hThread,isSaveDir) (ebBOOL)ebSendMessage(hThread,ebTM_SETSAVEDIR,(ebPARAM1)(_ebBOOL)(isSaveDir),(ebPARAM2)0)

/* ebBOOL ebThread_EnableBreak(ebHTHREAD hThread,_ebBOOL isBreak); */
#define ebThread_EnableBreak(hThread,isBreak) (ebBOOL)ebSendMessage(hThread,ebTM_ENABLEBREAK,(ebPARAM1)(_ebBOOL)(isBreak),(ebPARAM2)0)

/* ebWORD ebThread_GetErrorLine(ebHTHREAD hThread); */
#define ebThread_GetErrorLine(hThread) (ebWORD)ebSendMessage(hThread,ebTM_GETERRORLINE,(ebPARAM1)0,(ebPARAM2)0)

/* ebWORD ebThread_GetDialogCount(ebHTHREAD hThread); */
#define ebThread_GetDialogCount(hThread) (ebWORD)ebSendMessage(hThread,ebTM_GETDIALOGCOUNT,(ebPARAM1)0,(ebPARAM2)0)

/* ebDWORD ebThread_GetErrorNumber(ebHTHREAD hThread); */
#define ebThread_GetErrorNumber(hThread) (ebDWORD)ebSendMessage(hThread,ebTM_GETERRORNUMBER,(ebPARAM1)0,(ebPARAM2)0)

/* ebHINSTANCE ebThread_GetInstance(ebHTHREAD hThread); */
#define ebThread_GetInstance(hThread) (ebHINSTANCE)ebSendMessage(hThread,ebTM_GETINSTANCE,(ebPARAM1)0,(ebPARAM2)0)

/* long ebThread_GetLong(ebHTHREAD hThread,ebDWORD dwOffset); */
#define ebThread_GetLong(hThread,dwOffset) (long)ebSendMessage(hThread,ebTM_GETLONG,(ebPARAM1)(ebDWORD)(dwOffset),(ebPARAM2)0)

/* ebHSCRIPT ebThread_GetScript(ebHTHREAD hThread,ebINT context); */
#define ebThread_GetScript(hThread,context) (ebHSCRIPT)ebSendMessage(hThread,ebTM_GETSCRIPT,(ebPARAM1)(ebINT)(context),(ebPARAM2)0)

/* ebINT ebThread_GetState(ebHTHREAD hThread); */
#define ebThread_GetState(hThread) (ebINT)ebSendMessage(hThread,ebTM_GETSTATE,(ebPARAM1)0,(ebPARAM2)0)

/* ebWORD ebThread_GetWord(ebHTHREAD hThread,ebDWORD dwOffset); */
#define ebThread_GetWord(hThread,dwOffset) (ebWORD)ebSendMessage(hThread,ebTM_GETWORD,(ebPARAM1)(ebDWORD)(dwOffset),(ebPARAM2)0)

/* void ebThread_Interrupt(ebHTHREAD hThread,ebINT nCode,ebDWORD dwError); */
#define ebThread_Interrupt(hThread,nCode,dwError) ebSendMessage(hThread,ebTM_INTERRUPT,(ebPARAM1)(ebINT)(nCode),(ebPARAM2)(_ebWORD)(dwError))

/* ebBOOL ebThread_IsInterrupted(ebHTHREAD hThread); */
#define ebThread_IsInterrupted(hThread) (ebBOOL)ebSendMessage(hThread,ebTM_ISINTERRUPTED,(ebPARAM1)0,(ebPARAM2)0)

/* void ebThread_SetCommandLine(ebHTHREAD hThread,ebLPCTSTR lpNewCmdLine); */
#define ebThread_SetCommandLine(hThread,lpNewCmdLine) ebSendMessage(hThread,ebTM_SETCOMMANDLINE,(ebPARAM1)0,(ebPARAM2)(ebLPCTSTR)(lpNewCmdLine))

/* ebINT ebThread_SetEntryInfo(ebHTHREAD hThread,ebLPENTRYINFO lpei); */
#define ebThread_SetEntryInfo(hThread,lpei) (ebINT)ebSendMessage(hThread,ebTM_SETENTRYINFO,(ebPARAM1)0,(ebPARAM2)(ebLPENTRYINFO)(lpei))

/* void ebThread_SetHomeDir(ebHTHREAD hThread,ebLPCTSTR lpDir); */
#define ebThread_SetHomeDir(hThread,lpDir) ebSendMessage(hThread,ebTM_SETHOMEDIR,(ebPARAM1)0,(ebPARAM2)(ebLPCTSTR)(lpDir))

/* ebDWORD ebThread_SetLinkOptions(ebHTHREAD hThread,ebDWORD dwLinkOptions); */
#define ebThread_SetLinkOptions(hThread,dwLinkOptions) (ebDWORD)ebSendMessage(hThread,ebTM_SETLINKOPTIONS,(ebPARAM1)(ebDWORD)(dwLinkOptions),(ebPARAM2)0)

/* void ebThread_SetLong(ebHTHREAD hThread,ebDWORD dwOffset,long lValue); */
#define ebThread_SetLong(hThread,dwOffset,lValue) ebSendMessage(hThread,ebTM_SETLONG,(ebPARAM1)(ebDWORD)(dwOffset),(ebPARAM2)(long)(lValue))

/* void ebThread_SetPrintProc(ebHTHREAD hThread,long lParam,ebPRINTPROC lpfnPrintProc); */
#define ebThread_SetPrintProc(hThread,lParam,lpfnPrintProc) ebSendMessage(hThread,ebTM_SETPRINTPROC,(ebPARAM1)(ebLONG)(lParam),(ebPARAM2)(ebPRINTPROC)(lpfnPrintProc))

/* void ebThread_SetRuntimeErrorProc(ebHTHREAD hThread,long lParam,ebERRORPROC lpfnError); */
#define ebThread_SetRuntimeErrorProc(hThread,lParam,lpfnError) ebSendMessage(hThread,ebTM_SETRUNTIMEERRORPROC,(ebPARAM1)(lParam),(ebPARAM2)(ebERRORPROC)(lpfnError))

/* ebBOOL ebThread_SetStack(ebHTHREAD hThread,ebDWORD dwNewSize); */
#define ebThread_SetStack(hThread,dwNewSize) (ebBOOL)ebSendMessage(hThread,ebTM_SETSTACK,(ebPARAM1)dwNewSize,(ebPARAM2)0)

/* void ebThread_SetWord(ebHTHREAD hThread,ebDWORD dwOffset,_ebWORD wValue); */
#define ebThread_SetWord(hThread,dwOffset,wValue) ebSendMessage(hThread,ebTM_SETWORD,(ebPARAM1)(ebDWORD)(dwOffset),(ebPARAM2)(_ebWORD)(wValue))

/* ebINT ebThread_GetOptionBase(ebHTHREAD hThread); */
#define ebThread_GetOptionBase(hThread) (ebINT)ebSendMessage(hThread,ebTM_GETOPTIONBASE,(ebPARAM1)0,(ebPARAM2)0)

/* void ebThread_SetThis(ebHTHREAD hThread,ebDWORD dwThis); */
#define ebThread_SetThis(hThread,dwThis) ebSendMessage(hThread,ebTM_SETTHIS,(ebPARAM1)(ebDWORD)(dwThis),(ebPARAM2)0)

/* ebDWORD ebThread_GetThis(ebHTHREAD hThread); */
#define ebThread_GetThis(hThread) (ebDWORD)ebSendMessage(hThread,ebTM_GETTHIS,(ebPARAM1)0,(ebPARAM2)0)

/* void ebThread_SetHelpProc(ebHTHREAD hThread,ebHELPPROC lpfnHelpProc,long lParam); */
#define ebThread_SetHelpProc(hThread,lpfnHelpProc,lParam) ebSendMessage(hThread,ebTM_SETHELPPROC,(ebPARAM1)(lParam),(ebPARAM2)(ebHELPPROC)(lpfnHelpProc))

/* ebWORD ebThread_GetStopCondition(ebHTHREAD hThread); */
#define ebThread_GetStopCondition(hThread) (ebWORD)ebSendMessage(hThread,ebTM_GETSTOPCONDITION,0,0)

/* void ebThread_GetRuntimeErrorProc(ebHTHREAD hThread,long ebFAR *lplParam,ebERRORPROC ebFAR *lplpfnError); */
#define ebThread_GetRuntimeErrorProc(hThread,lplParam,lplpfnError) ebSendMessage(hThread,ebTM_GETRUNTIMEERRORPROC,(ebPARAM1)(lplParam),(ebPARAM1)(ebERRORPROC ebFAR *)(lplpfnError))

/* ebWORD ebThread_GetCurrentLineNumber(ebHTHREAD hThread); */
#define ebThread_GetCurrentLineNumber(hThread) (ebWORD)ebSendMessage(hThread,ebTM_GETCURRENTLINENUMBER,0,0)

/* ebWORD ebThread_GetLastErrorLine(ebHTHREAD hThread); */
#define ebThread_GetLastErrorLine(hThread) (ebWORD)ebSendMessage(hThread,ebTM_GETLASTERRORLINE,0,0)

/* void ebThread_SetEntryExitProc(ebHTHREAD hThread, ebENTRYEXITPROC lpfnEntryExitProc, long value); */
#define ebThread_SetEntryExitProc(hThread, lpfnEntryExitProc, value) ebSendMessage(hThread,ebTM_SETENTRYEXITPROC,(ebPARAM1)(lpfnEntryExitProc),(ebPARAM2)(value))

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * (C)ode (M)essages
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

#define ebCM_GETSIZE		0		/* gets the size of an ebHCODE */

/* ebDWORD ebAPI ebCode_GetSize(ebHCODE hCode); */
#define ebCode_GetSize(hCode) ebSendMessage(hCode,ebCM_GETSIZE,0,(ebPARAM2)(ebHCODE)(hCode))

/* ebLPVOID ebAPI ebCode_GetPointer(ebHCODE hCode); */
#define ebCode_GetPointer(hCode) ((ebLPVOID)(hCode))

/* void ebAPI ebCode_Free(ebHCODE); */
#define ebCode_Free(hCode) ebFreePtr((ebLPVOID)(hCode))

/* ebHCODE ebAPI ebCode_Create(ebLPVOID lpPointer); */
#define ebCode_Create(p) ((ebHCODE)(p))

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * ebSendMessage -- used by object message macros
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

long ebAPI ebSendMessageA(ebHOBJECT hObject,ebUINT message,ebPARAM1 Param1,ebPARAM2 Param2);
long ebAPI ebSendMessageW(ebHOBJECT hObject,ebUINT message,ebPARAM1 Param1,ebPARAM2 Param2);

#ifdef EBWIDE
#define ebSendMessage ebSendMessageW
#else
#define ebSendMessage ebSendMessageA
#endif	/* EBWIDE */

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Localization stuff
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

typedef struct tagebCOUNTRYA {
	short iDate;	  		 		/* date format: 1=DMY, 2=YMD, 0=MDY */
	short iTime;	 		 		/* time format: 1=24 Hour Format, 0=12 Hour Format */
	short iCurrencyPos;   		/* positive currency format (0=$1, 1=1$, 2=$ 1, 3=1 $) */
	short iCurrencyNeg;   		/* negative currency format (0=($1), 1=-$1, 2=$-1, 3=$1-, 4=(1$), 5=-1$, 6=1-$, 7=1$-, 8=-1 $, 9=-$ 1, 10=1 $- */
	short iCurrencyDigits; 		/* number of decimal digits (currency only) */
	short iTLZero;	 				/* leading zero on time: 0=no leading zero (e.g., "9:15"), 1=leading zero (e.g., "09:15") */
	short FirstDayOfWeek;		/* first day of the week (1=Sunday, 2=Monday, ... 7=Saturday */
	short FirstWeekOfYear;		/* first week of the year (1=week in which January 1 occurs, 2=first week with at least 4 days in new year, 3=first full week of the year */
	char szDate[5];   			/* NUL terminated date separator (i.e., "/" or "-") */
	char szTime[5];	 			/* NUL terminated time separator (i.e., ":") */
	char szAM[10];		 			/* NUL terminated AM string (i.e., "AM") */
	char szPM[10];			 		/* NUL terminated PM string (i.e., "PM") */
	char szCurrency[5];			/* NUL terminated currency symbol (i.e., "$") */
	char szThousand[5];			/* NUL terminated thousands separator (i.e., ",") */
	char szDecimal[5];	  		/* NUL terminated decimal separator (i.e., ".") */
	char szShortDate[40];	  	/* NUL terminated short date format (i.e., "d/m/yy") */
	char szLongDate[80]; 		/* NUL terminated long date format (i.e., dddd', 'MMMM' 'dd', 'yyyy) */
	char szLongMonths[256]; 	/* long months, each separated with a comma (e.g., "January,February,...") */
	char szShortMonths[128];	/* abbreviated months, each separated with a comma (e.g., "Jan,Feb,Mar,...") */
	char szLongDays[128];		/* long days of the week, each separated with a comma (e.g., "Sunday,Monday,...") */
	char szShortDays[64];		/* short days of the week, each separated with a comma (e.g., "Sun,Mon,Tue,...") */
} ebCOUNTRYA,ebFAR *ebLPCOUNTRYA;

typedef struct tagebCOUNTRYW {
	short iDate;	  		 		/* date format: 1=DMY, 2=YMD, 0=MDY */
	short iTime;	 		 		/* time format: 1=24 Hour Format, 0=12 Hour Format */
	short iCurrencyPos;   		/* positive currency format (0=$1, 1=1$, 2=$ 1, 3=1 $) */
	short iCurrencyNeg;   		/* negative currency format (0=($1), 1=-$1, 2=$-1, 3=$1-, 4=(1$), 5=-1$, 6=1-$, 7=1$-, 8=-1 $, 9=-$ 1, 10=1 $- */
	short iCurrencyDigits;		/* number of decimal digits (currency only) */
	short iTLZero;	 		 		/* leading zero on time: 0=no leading zero (e.g., "9:15"), 1=leading zero (e.g., "09:15") */
	short FirstDayOfWeek;		/* first day of the week (1=Sunday, 2=Monday, ... 7=Saturday */
	short FirstWeekOfYear;		/* first week of the year (1=week in which January 1 occurs, 2=first week with at least 4 days in new year, 3=first full week of the year */
	ebWCHAR szDate[5];    		/* NUL terminated date separator (i.e., "/" or "-") */
	ebWCHAR szTime[5];	 		/* NUL terminated time separator (i.e., ":") */
	ebWCHAR szAM[10];		 		/* NUL terminated AM string (i.e., "AM") */
	ebWCHAR szPM[10];		  		/* NUL terminated PM string (i.e., "PM") */
	ebWCHAR szCurrency[5]; 		/* NUL terminated currency symbol (i.e., "$") */
	ebWCHAR szThousand[5]; 		/* NUL terminated thousands separator (i.e., ",") */
	ebWCHAR szDecimal[5];		/* NUL terminated decimal separator (i.e., ".") */
	ebWCHAR szShortDate[40];  	/* NUL terminated short date format (i.e., "d/m/yy") */
	ebWCHAR szLongDate[80]; 	/* NUL terminated long date format (i.e., dddd', 'MMMM' 'dd', 'yyyy) */
	ebWCHAR szLongMonths[256];	/* long months, each separated with a comma (e.g., "January,February,...") */
	ebWCHAR szShortMonths[128];/* abbreviated months, each separated with a comma (e.g., "Jan,Feb,Mar,...") */
	ebWCHAR szLongDays[128];	/* long days of the week, each separated with a comma (e.g., "Sunday,Monday,...") */
	ebWCHAR szShortDays[64];	/* short days of the week, each separated with a comma (e.g., "Sun,Mon,Tue,...") */
} ebCOUNTRYW,ebFAR *ebLPCOUNTRYW;

#ifdef EBWIDE
typedef ebCOUNTRYW ebCOUNTRY;
typedef ebLPCOUNTRYW ebLPCOUNTRY;
#else
typedef ebCOUNTRYA ebCOUNTRY;
typedef ebLPCOUNTRYA ebLPCOUNTRY;
#endif	/* EBWIDE */

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Registration APIs
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

typedef void (ebCALLBACK _ebCALLBACKPROC)(ebHTHREAD hThread,_ebWORD wCmdNum,ebINT iNumArgs,ebLPLPVOID lplpArgs);
typedef _ebCALLBACKPROC *ebCALLBACKPROC;

ebBOOL ebAPI ebRegisterExtensionsW(ebHINSTANCE hInstance,ebLPCWSTR lpName,ebLPCVOID lpData,ebCALLBACKPROC lpfnCallback);
ebBOOL ebAPI ebRegisterExtensionsA(ebHINSTANCE hInstance,ebLPCSTR lpName,ebLPCVOID lpData,ebCALLBACKPROC lpfnCallback);

#ifdef EBWIDE
#define ebRegisterExtensions ebRegisterExtensionsW
#else
#define ebRegisterExtensions ebRegisterExtensionsA
#endif	/* EBWIDE */

ebBOOL ebCAPI ebRegisterExtensionsExA(ebHINSTANCE hInstance,ebLPCSTR lpName,ebCALLBACKPROC lpfnCallback,...);
ebBOOL ebCAPI ebRegisterExtensionsExW(ebHINSTANCE hInstance,ebLPCWSTR lpName,ebCALLBACKPROC lpfnCallback,...);

#ifdef EBWIDE
#define ebRegisterExtensionsEx ebRegisterExtensionsExW
#else
#define ebRegisterExtensionsEx ebRegisterExtensionsExA
#endif	/* EBWIDE */

ebBOOL ebAPI ebRegisterExtensionsExVA(ebHINSTANCE hInstance,ebLPCSTR lpName,ebCALLBACKPROC lpfnCallback,ebLPCVOID lpParams);
ebBOOL ebAPI ebRegisterExtensionsExVW(ebHINSTANCE hInstance,ebLPCWSTR lpName,ebCALLBACKPROC lpfnCallback,ebLPCVOID lpParams);

#ifdef EBWIDE
#define ebRegisterExtensionsExV ebRegisterExtensionsExVW
#else
#define ebRegisterExtensionsExV ebRegisterExtensionsExVA
#endif	/* EBWIDE */

void ebAPI ebUnRegisterExtensionsA(ebHINSTANCE hInstance,ebLPCSTR lpName);
void ebAPI ebUnRegisterExtensionsW(ebHINSTANCE hInstance,ebLPCWSTR lpName);

#ifdef EBWIDE
#define ebUnRegisterExtensions ebUnRegisterExtensionsW
#else
#define ebUnRegisterExtensions ebUnRegisterExtensionsA
#endif	/* EBWIDE */

#ifdef ebHAVE_OLE	/* OLE is defined only on these platforms */

#define OLE_OBJECT_CONST_START		1		/* OLE object constants start here */

#if defined(EBWIN) || defined(EBMAC)
#define OLE_OBJECT_CONST_END			1000	/* this many OLE object constant can be defined */
#endif /* EBWIN | EBMAC */

#if defined(EBWIN32)
#define OLE_OBJECT_CONST_END 			10000	/* this many OLE object constant can be defined */
#endif /* EBWIN32 */

void ebAPI ebRegisterOleObject(ebHOBJECT hObject,ebDWORD dwConst,ebLPDISPATCH lpDispatch);
void ebAPI ebRegisterOleObjectEx(ebHOBJECT hObject,ebDWORD dwConst,ebLPDISPATCH lpDispatch,ebLCID lcid,_ebBOOL isUnicode);

#define ebMAKETYPELIBACCESSFLAGS(flib,ffunc,fvar)	(ebMAKEDWORD(ebMAKEWORD(fvar,ffunc),flib))

#define EBREGISTERTYPELIB_OBJECTSONLY	0x0001	/* Only register objects */

ebBOOL ebAPI ebRegisterTypeLibA(ebHINSTANCE hInstance, ebLPCSTR pszName, ebLPCSTR pszTypeLibFile, ebDWORD uFlags);
ebBOOL ebAPI ebRegisterTypeLibW(ebHINSTANCE hInstance, ebLPCWSTR pszName, ebLPCWSTR pszTypeLibFile, ebDWORD uFlags);

#ifdef EBWIDE
#define ebRegisterTypeLib ebRegisterTypeLibW
#else
#define ebRegisterTypeLib ebRegisterTypeLibA
#endif /* EBWIDE */

ebBOOL ebAPI ebRegisterITypeLibA(ebHINSTANCE hInstance, ebLPCSTR pszName, ebLPTYPELIB lpTypeLib, ebDWORD uFlags);
ebBOOL ebAPI ebRegisterITypeLibW(ebHINSTANCE hInstance, ebLPCWSTR pszName, ebLPTYPELIB lpTypeLib, ebDWORD uFlags);

#ifdef EBWIDE
#define ebRegisterITypeLib ebRegisterITypeLibW
#else
#define ebRegisterITypeLib ebRegisterITypeLibA
#endif /* EBWIDE */

ebBOOL ebAPI ebRegisterITypeInfoA(ebHINSTANCE hInstance, ebLPCSTR pszName, ebLPTYPEINFO lpTypeInfo, ebDWORD uFlags);
ebBOOL ebAPI ebRegisterITypeInfoW(ebHINSTANCE hInstance, ebLPCWSTR pszName, ebLPTYPEINFO lpTypeInfo, ebDWORD uFlags);

#ifdef EBWIDE
#define ebRegisterITypeInfo ebRegisterITypeInfoW
#else
#define ebRegisterITypeInfo ebRegisterITypeInfoA
#endif /* EBWIDE */

#endif	/* ebHAVE_OLE */

/* Flags passed in to the ebInit function */
#define EBINIT_USECOMPILER				0x0001	/* load the compiler */
#define EBINIT_USERUNTIME				0x0002	/* load the runtime */
#define EBINIT_SEARCH_DIRECTORY 		0x0004	/* search directory for EBL files */
#define EBINIT_SEARCH_INI				0x0008	/* search INI file for EBL files */
#define EBINIT_SEARCH_PROC				0x0010	/* use the callback proc for EBL names */
#define EBINIT_USE_GLOBAL_PCODE_SECTION	0x0020	/* reserved */
#define EBINIT_NO_OLEINITIALIZE			0x0040	/* don't call OleInitialize() */

typedef ebBOOL (ebCALLBACK _ebEXTENUMPROCA)(ebLPSTR lpFileName,long lParam);
typedef _ebEXTENUMPROCA *ebEXTENUMPROCA;

typedef ebBOOL (ebCALLBACK _ebEXTENUMPROCW)(ebLPWSTR lpFileName,long lParam);
typedef _ebEXTENUMPROCW *ebEXTENUMPROCW;

#ifdef EBWIDE
typedef ebEXTENUMPROCW ebEXTENUMPROC;
#else
typedef ebEXTENUMPROCA ebEXTENUMPROC;
#endif	/* EBWIDE */

ebHINSTANCE ebAPI ebInitA(_ebWORD wFlags,ebEXTENUMPROCA lpfnGetExt,ebLPINT lpError,long lParam,ebINT iInstanceExtra);
ebHINSTANCE ebAPI ebInitW(_ebWORD wFlags,ebEXTENUMPROCW lpfnGetExt,ebLPINT lpError,long lParam,ebINT iInstanceExtra);

#ifdef EBWIDE
#define ebInit ebInitW
#else
#define ebInit ebInitA
#endif	/* EBWIDE */

void ebAPI ebTerm(ebHINSTANCE hInstance);

typedef ebHINSTANCE (ebAPI EB_INITPROCA)(_ebWORD wFlags,ebEXTENUMPROCA lpfnGetExt,ebLPINT lpError,long lParam,ebINT iInstanceExtra);
typedef EB_INITPROCA *ebINITPROCA;
typedef ebHINSTANCE (ebAPI EB_INITPROCW)(_ebWORD wFlags,ebEXTENUMPROCW lpfnGetExt,ebLPINT lpError,long lParam,ebINT iInstanceExtra);
typedef EB_INITPROCW *ebINITPROCW;

#ifdef EBWIDE
typedef EB_INITPROCW EB_INITPROC;
#else
typedef EB_INITPROCA EB_INITPROC;
#endif	/* EBWIDE */

typedef void (ebAPI EB_TERMPROC)(ebHINSTANCE hInstance);
typedef EB_TERMPROC *ebTERMPROC;

#endif	/* !RC_INVOKED */

#define VARNAMESZ			81		/* this many characters allowed in the name of a variable (includes NUL) */

/* --------------------------------------------------------------------------
 * Error messages used by the BasicScript APIs
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

#define ebERR_SUCCESSFUL				0	/* Succesful operation */
#define ebERR_OUTOFMEMORY				1	/* insufficient memory for operation */
#define ebERR_ENTRYNOTFOUND			2	/* can't find specified entry point */
#define ebERR_BADCODE					3	/* invalid code */
#define ebERR_VERSIONMISMATCH			4	/* compiler/runtime versions don't match */
#define ebERR_CANTLOADCOMPILER		5	/* error loading the compiler */
#define ebERR_CANTLOADRUNTIME			6	/* error loading the runtime */
#define ebERR_CANTLOADEXTENSIONS		7	/* error loading extensions */
#define ebERR_RUNTIMEINITERROR		8	/* error initializing the runtime */
#define ebERR_ENTRYWRONGTYPE			9	/* entry point not same as requested type */
#define ebERR_BADARGUMENTTYPE			10	/* an argument's type did not match */
#define ebERR_BADARGUMENTCOUNT		11	/* the argument count is different */
#define ebERR_BADSYMBOL					12	/* bad symbol table */
#define ebERR_BADRETTYPE				13	/* return argument's type does not match */
#define ebERR_INVALIDARRAYHEADER		14	/* invalid array header */
#define ebERR_CANTREDIMFIXED			15	/* cannot redimension a fixed array */
#define ebERR_INVALIDDIMENSIONS		16	/* invalid number of dimensions */
#define ebERR_UNSUPPORTEDDATATYPE	17	/* unsupported data type */
#define ebERR_COMPILERERROR			18	/* error compiling the script */
#define ebERR_CANTFINDEXTENSION		19	/* unable to locate extension */
#define ebERR_LINKERROR					20	/* unable to resolve types during consolidation of public variable space */
#define ebERR_PARSEERROR				21	/* syntax error during parsing */
#define ebERR_VARIABLENOTFOUND		22	/* specified variable was not found */
#define ebERR_WRONGOBJECTTYPE			23	/* wrong type of object (ebHOBJECT) was passed in */
#define ebERR_VARIABLEWRONGTYPE		24	/* variable is wrong type for operation */
#define ebERR_WRONGDIMENSIONS			25	/* wrong number of dimensions appears in parse expression */
#define ebERR_INDEXOUTOFBOUNDS		26	/* one of the specified indexes is out of bounds */
#define ebERR_TYPEMISMATCH				27	/* a variable is already defined as a different type */
#define ebERR_ARRAYMISMATCH			28	/* a variable is already defined with different dimensions */
#define ebERR_USERTYPEMISMATCH		29	/* a user-defined type is defined differently in another script */
#define ebERR_THREADNOTIDLE			30	/* thread needs to be idle for this function */
#define ebERR_NOTIMPLEMENTED			31	/* function call is not implemented */
#define ebERR_OUTOFCONTEXT				32	/* can't find context for local variable in the call stack */
#define ebERR_CANTINITPUBLIC			33	/* can't initialize the dispatcher */
#define ebERR_INVALIDPARAMETER		34	/* a passed-in parameter was invalid */

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Compiler API
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

typedef void (ebCALLBACK _ebERRORPROCA)(long lParam,ebLPCSTR lpErrText,ebDWORD dwErrNum,_ebWORD wLineNo,_ebWORD wCharPos,ebLPCSTR lpSource,ebLPCSTR lpHelpFile,ebDWORD dwHelpContext);
typedef _ebERRORPROCA *ebERRORPROCA;

typedef void (ebCALLBACK _ebERRORPROCW)(long lParam,ebLPCWSTR lpErrText,ebDWORD dwErrNum,_ebWORD wLineNo,_ebWORD wCharPos,ebLPCWSTR lpSource,ebLPCWSTR lpHelpFile,ebDWORD dwHelpContext);
typedef _ebERRORPROCW *ebERRORPROCW;

#ifdef EBWIDE
typedef ebERRORPROCW ebERRORPROC;
#else
typedef ebERRORPROCA ebERRORPROC;
#endif	/* EBWIDE */

typedef ebINT (ebCALLBACK _ebHELPPROCA)(ebHTHREAD hThread,ebHWND hWnd,ebLPCSTR lpHelpFileName,ebDWORD dwHelpContext,long lParam);
typedef _ebHELPPROCA *ebHELPPROCA;

typedef ebINT (ebCALLBACK _ebHELPPROCW)(ebHTHREAD hThread,ebHWND hWnd,ebLPCWSTR lpHelpFileName,ebDWORD dwHelpContext,long lParam);
typedef _ebHELPPROCW *ebHELPPROCW;

#ifdef EBWIDE
typedef ebHELPPROCW ebHELPPROC;
#else
typedef ebHELPPROCA ebHELPPROC;
#endif	/* EBWIDE */

typedef ebINT (ebCALLBACK _ebLOADSTRINGPROCA)(long lParam,_ebWORD id,ebLPSTR lpDest,_ebWORD wDestSz);
typedef _ebLOADSTRINGPROCA *ebLOADSTRINGPROCA;

typedef ebINT (ebCALLBACK _ebLOADSTRINGPROCW)(long lParam,_ebWORD id,ebLPWSTR lpDest,_ebWORD wDestSz);
typedef _ebLOADSTRINGPROCW *ebLOADSTRINGPROCW;

#ifdef EBWIDE
typedef ebLOADSTRINGPROCW ebLOADSTRINGPROC;
#else
typedef ebLOADSTRINGPROCA ebLOADSTRINGPROC;
#endif	/* EBWIDE */

#if defined(EBMAC) && HAVE_ANYDIALOGS
#define ebDLGPROC_SHOW		0		/* dialog about to be displayed */
#define ebDLGPROC_DESTROY	1		/* dialog about to be destroyed */
#endif

/* (C)ompile (F)lags */
#define CF_YIELD					0x0001		/* set if yielding is performed during compile */
#define CF_USELOCALERRORPROC	0x0002		/* use the error procedure contained in the ebCOMPILESTRUCT rather than the instance */
#define CF_EXPLICITVARS			0x0004		/* user must explicitly declare all variables */
#define CF_USELINENUMBERPROC	0x0008		/* use the line number callback */
#define CF_USECONSTPROC			0x0010		/* use the preprocessor constant callback */
#define CF_EXPLICITRTNS			0x0020		/* user must explicitly declare calls to functions/subs */
#define CF_64K_LIMIT				0x0040		/* limits the compiler to generating Windows compatible code */
#define CF_USEOLECONSTPROC		0x0080		/* Enables External Ole Constant function */
#define CF_RESERVED1				0x0100		/* reserved for internal use */
#define CF_RESERVED2				0x0200		/* reserved for internal use */
#define CF_OPTIONEXPLICIT		(CF_EXPLICITVARS | CF_EXPLICITRTNS)	/* assume Option Explicit by default */
#define CF_RESERVED3				0x0400		/* reserved for internal use */
#define CF_OLEEXPLICIT			0x0800		/* error if meth or prop does not exist when compiler has the type library */
#define CF_RESERVED4				0x1000		/* skips ByRef/ByVal errors in the compiler for 2.1 compatibility */

#define CS_VERSION				1				/* current version of the compile struct */

typedef void (ebCALLBACK _ebLINENUMBERPROC)(long lParam,_ebWORD wLineNo);
typedef _ebLINENUMBERPROC *ebLINENUMBERPROC;

typedef ebINT (ebCALLBACK _ebCONSTPROCA)(long lParam,ebLPCSTR lpName,ebLPVOID lpDest);
typedef _ebCONSTPROCA *ebCONSTPROCA;

typedef ebINT (ebCALLBACK _ebCONSTPROCW)(long lParam,ebLPCWSTR lpName,ebLPVOID lpDest);
typedef _ebCONSTPROCW *ebCONSTPROCW;

#ifdef EBWIDE
typedef ebCONSTPROCW ebCONSTPROC;
#else
typedef ebCONSTPROCA ebCONSTPROC;
#endif	/* EBWIDE */

typedef ebINT (ebCALLBACK _ebOLECONSTPROCA)(long lParam,ebLPCSTR lpName,ebLPDWORD lpdwValue);
typedef _ebOLECONSTPROCA *ebOLECONSTPROCA;

typedef ebINT (ebCALLBACK _ebOLECONSTPROCW)(long lParam,ebLPCWSTR lpName,ebLPDWORD lpdwValue);
typedef _ebOLECONSTPROCW *ebOLECONSTPROCW;

#ifdef EBWIDE
typedef ebOLECONSTPROCW ebOLECONSTPROC;
#else
typedef ebOLECONSTPROCA ebOLECONSTPROC;
#endif	/* EBWIDE */

typedef struct tagCOMPILESTRUCTA {
	ebWORD wVersion;					/* version of this structure (CS_VERSION) */
	ebWORD wFlags;						/* Flags for the compile */
	ebLPCSTR lpText;	 				/* Script to be compiled */
	ebHCODE hCode; 		  			/* Compile code, set on successful return */
	ebHINSTANCE hInstance;			/* instance of the application (returned fro ebInit) */
	ebDWORD dwError;	  				/* error number, if compile stopped due to an error */
	ebWORD wLineNo;					/* line number where error occurred, if compile stopped due to an error */
	ebWORD wCharPos;					/* character position where error occurred, if compile stopped due to an error */
	ebERRORPROCA lpfnError;			/* routine to call when an error occurs -- only called if CF_USELOCALERRORPROC is set */
	long ErrorData;					/* data to pass through to error routine */
	ebLINENUMBERPROC lpfnLineNum;	/* pointer to line number procedure, only called if CF_USELINENUMBERPROC is set */
	long LineNumData;					/* data to pass through to the line number routine */
	ebCONSTPROCA lpfnConst;			/* pointer to routine to call to resolve preprocessor constants */
	long ConstData;					/* data to pass through to the routine that resolved preprocessor constants */
	ebOLECONSTPROCA lpfnOleConst;	/* pointer to a routine to call to test identifiers as ole constants */
	long OleConstData;				/* date to pass through to the lpfnOleConst routine */
} ebCOMPILESTRUCTA, ebFAR *ebLPCOMPILESTRUCTA;

typedef struct tagCOMPILESTRUCTW {
	ebWORD wVersion;					/* version of this structure (CS_VERSION) */
	ebWORD wFlags;						/* Flags for the compile */
	ebLPCWSTR lpText;	 				/* Script to be compiled */
	ebHCODE hCode; 		  			/* Compile code, set on successful return */
	ebHINSTANCE hInstance;			/* instance of the application (returned fro ebInit) */
	ebDWORD dwError;					/* error number, if compile stopped due to an error */
	ebWORD wLineNo;					/* line number where error occurred, if compile stopped due to an error */
	ebWORD wCharPos;					/* character position where error occurred, if compile stopped due to an error */
	ebERRORPROCW lpfnError;			/* routine to call when an error occurs -- only called if CF_USELOCALERRORPROC is set */
	long ErrorData;					/* data to pass through to error routine */
	ebLINENUMBERPROC lpfnLineNum;	/* pointer to line number procedure, only called if CF_USELINENUMBERPROC is set */
	long LineNumData;					/* data to pass through to the line number routine */
	ebCONSTPROCW lpfnConst;			/* pointer to routine to call to resolve preprocessor constants */
	long ConstData;					/* data to pass through to the routine that resolved preprocessor constants */
	ebOLECONSTPROCW lpfnOleConst;	/* pointer to a routine to call to test identifiers as ole constants */
	long OleConstData;				/* date to pass through to the lpfnOleConst routine */
} ebCOMPILESTRUCTW,ebFAR *ebLPCOMPILESTRUCTW;

#ifdef EBWIDE
typedef ebCOMPILESTRUCTW ebCOMPILESTRUCT;
typedef ebLPCOMPILESTRUCTW ebLPCOMPILESTRUCT;
#else
typedef ebCOMPILESTRUCTA ebCOMPILESTRUCT;
typedef ebLPCOMPILESTRUCTA ebLPCOMPILESTRUCT;
#endif	/* EBWIDE */

ebWORD ebAPI ebCompileA(ebLPCOMPILESTRUCTA lpCompile);
ebWORD ebAPI ebCompileW(ebLPCOMPILESTRUCTW lpCompile);

#ifdef EBWIDE
#define ebCompile ebCompileW
#else
#define ebCompile ebCompileA
#endif	/* EBWIDE */

ebWORD ebAPI ebRegisterScriptA(ebLPCOMPILESTRUCTA lpCompile,ebLPCSTR lpName);
ebWORD ebAPI ebRegisterScriptW(ebLPCOMPILESTRUCTW lpCompile,ebLPCWSTR lpName);

#ifdef EBWIDE
#define ebRegisterScript ebRegisterScriptW
#else
#define ebRegisterScript ebRegisterScriptA
#endif	/* EBWIDE */

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Execution API
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

typedef void (ebCALLBACK _ebPCODECALLBACKPROC)(ebHTHREAD hThread,long lParam);
typedef _ebPCODECALLBACKPROC *ebPCODECALLBACKPROC;

typedef void (ebCALLBACK _ebPRINTPROCA)(ebHTHREAD hThread,ebLPCSTR lpText,ebINT iTextLen,long lParam);
typedef _ebPRINTPROCA *ebPRINTPROCA;

typedef void (ebCALLBACK _ebPRINTPROCW)(ebHTHREAD hThread,ebLPCWSTR lpText,ebINT iTextLen,long lParam);
typedef _ebPRINTPROCW *ebPRINTPROCW;

typedef ebUINT (ebCALLBACK _ebNATIVETOPORTABLEPROC)(ebLPBYTE lpDest,ebUINT iDestSizeInBytes,ebLPTSTR lpSource,ebUINT iSourceSizeInChars,long lParam);
typedef _ebNATIVETOPORTABLEPROC *ebNATIVETOPORTABLEPROC;

typedef ebUINT (ebCALLBACK _ebPORTABLETONATIVEPROC)(ebLPTSTR lpDest,ebUINT iDestSizeInChars,ebLPBYTE lpSource,ebUINT iSourceSizeInBytes,long lParam);
typedef _ebPORTABLETONATIVEPROC *ebPORTABLETONATIVEPROC;

typedef void (ebCALLBACK _ebENTRYEXITPROC)(ebHTHREAD hThread,ebBOOL bEntering,ebBOOL bInError,long lParam);
typedef _ebENTRYEXITPROC *ebENTRYEXITPROC;

#ifdef EBWIDE
typedef ebPRINTPROCW ebPRINTPROC;
#else
typedef ebPRINTPROCA ebPRINTPROC;
#endif	/* EBWIDE */

#if (defined(EBWIN) || defined(EBWIN32))	/* control knowledge routines only defined on these platforms */
/* (C)ontrol (K)nowledge constants */
#define CK_RADIO			1	/* radio */
#define CK_CHECKBOX		2	/* checkbox */
#define CK_LISTBOX		3	/* listbox */
#define CK_COMBOBOX		4	/* combobox */
#define CK_STATIC			5	/* static */
#define CK_EDIT			6	/* edit */
#define CK_DIALOG			7	/* dialog */
#define CK_PUSHBUTTON	8	/* pushbutton */

typedef ebBOOL (ebCALLBACK *ebCKPROC)(ebHWND hWnd,ebINT type);
#endif	/* EBWIN || EBWIN32 */

#define ENTRYNAMESZ		81	/* this many characters allowed in the name of an entry point */

typedef ebHSCRIPT (ebCALLBACK _ebREQUESTORPROCA)(ebHTHREAD hThread,ebLPCSTR lpEntryName,long lParam);
typedef _ebREQUESTORPROCA *ebREQUESTORPROCA;

typedef ebHSCRIPT (ebCALLBACK _ebREQUESTORPROCW)(ebHTHREAD hThread,ebLPCWSTR lpEntryName,long lParam);
typedef _ebREQUESTORPROCW *ebREQUESTORPROCW;

#ifdef EBWIDE
typedef ebREQUESTORPROCW ebREQUESTORPROC;
#else
typedef ebREQUESTORPROCA ebREQUESTORPROC;
#endif	/* EBWIDE */

typedef struct tagebPARAMA {
	ebWORD wType;	  					/* type of this parameter -- any of the TYP_* identifiers */
	char szExtType[VARNAMESZ];		/* extra type information (structure name or object type) */
} ebPARAMA,ebFAR *ebLPPARAMA;

typedef struct tagebPARAMW {
	ebWORD wType;	  					/* type of this parameter -- any of the TYP_* identifiers */
	ebWCHAR szExtType[VARNAMESZ];	/* extra type information (structure name or object type) */
} ebPARAMW,ebFAR *ebLPPARAMW;

#ifdef EBWIDE
typedef ebPARAMW ebPARAM;
typedef ebLPPARAMW ebLPPARAM;
#else
typedef ebPARAMA ebPARAM;
typedef ebLPPARAMA ebLPPARAM;
#endif	/* EBWIDE */

typedef struct tagebENTRYINFOA {
	char szEntry[ENTRYNAMESZ];		/* name of the entry point, like "main" (NUL terminated). If first byte NUL, then dwEntry is used */
	ebDWORD dwEntry;					/* entry info for optimized execution (only used if szEntry[0] is '\0') */
	ebWORD wReserved;					/* reserved field */
	ebWORD wParms;						/* number of parameters being passed to entry point */
	ebLPPARAMA lpParms;				/* pointer to an array of parameter types (NULL if no parameters) */
	ebPARAMA RetParm;					/* return value, if entry is a function */
	ebBOOL isFunc;						/* TRUE if this is a function, FALSE if subroutine */
} ebENTRYINFOA,ebFAR *ebLPENTRYINFOA;

typedef struct tagebENTRYINFOW {
	ebWCHAR szEntry[ENTRYNAMESZ];	/* name of the entry point, like "main" (NUL terminated). If first byte NUL, then dwEntry is used */
	ebDWORD dwEntry;					/* entry info for optimized execution (only used if szEntry[0] is '\0') */
	ebWORD wReserved;					/* reserved field */
	ebWORD wParms;						/* number of parameters being passed to entry point */
	ebLPPARAMW lpParms;				/* pointer to an array of parameter types (NULL if no parameters) */
	ebPARAMW RetParm;					/* return value, if entry is a function */
	ebBOOL isFunc;						/* TRUE if this is a function, FALSE if subroutine */
} ebENTRYINFOW,ebFAR *ebLPENTRYINFOW;

#ifdef EBWIDE
typedef ebENTRYINFOW ebENTRYINFO;
typedef ebLPENTRYINFOW ebLPENTRYINFO;
#else
typedef ebENTRYINFOA ebENTRYINFO;
typedef ebLPENTRYINFOA ebLPENTRYINFO;
#endif	/* EBWIDE */

ebINT ebAPI ebCheckEntryA(ebHOBJECT hObject,ebLPENTRYINFOA lpei);
ebINT ebAPI ebCheckEntryW(ebHOBJECT hObject,ebLPENTRYINFOW lpei);
#ifdef EBWIDE
#define ebCheckEntry ebCheckEntryW
#else
#define ebCheckEntry ebCheckEntryA
#endif	/* EBWIDE */

ebLPVOID ebAPI ebParm(ebHTHREAD hThread,ebINT iIndex);

#define ES_VERSION			1	/* version for the EXECUTESTRUCT */

typedef struct tagebEXECUTESTRUCTA {
	ebWORD wVersion;				/* version of this structure (use ES_VERSION) */
	ebHINSTANCE hInstance;		/* instance of the applicaiton (returned from ebInit) */
	ebENTRYINFOA ei;				/* entry point information */
	ebHCODE hCode;					/* compiled code */
	ebLPCSTR lpCmdLine;			/* far pointer to command line args, or NULL if none */
	ebWORD wLineNo;				/* line number with the error (set on exit) */
	ebDWORD dwError;				/* error number (set on exit) */
	ebDWORD dwStackSz;			/* size of the stack (0 means use default) */
	ebLPVOID lpAppData;			/* passed through to the callbacks as LONG 0 */
} ebEXECUTESTRUCTA,ebFAR *ebLPEXECUTESTRUCTA;

typedef struct tagebEXECUTESTRUCTW {
	ebWORD wVersion;				/* version of this structure (use ES_VERSION) */
	ebHINSTANCE hInstance;		/* instance of the applicaiton (returned from ebInit) */
	ebENTRYINFOW ei;				/* entry point information */
	ebHCODE hCode;					/* compiled code */
	ebLPCWSTR lpCmdLine;			/* far pointer to command line args, or NULL if none */
	ebWORD wLineNo;				/* line number with the error (set on exit) */
	ebDWORD dwError;				/* error number (set on exit) */
	ebDWORD dwStackSz;			/* size of the stack (0 means use default) */
	ebLPVOID lpAppData;			/* passed through to the callbacks as LONG 0 */
} ebEXECUTESTRUCTW,ebFAR *ebLPEXECUTESTRUCTW;

#ifdef EBWIDE
typedef ebEXECUTESTRUCTW ebEXECUTESTRUCT;
typedef ebLPEXECUTESTRUCTW ebLPEXECUTESTRUCT;
#else
typedef ebEXECUTESTRUCTA ebEXECUTESTRUCT;
typedef ebLPEXECUTESTRUCTA ebLPEXECUTESTRUCT;
#endif	/* EBWIDE */

ebINT ebCAPI ebExecuteA(ebLPEXECUTESTRUCTA lpes,...);
ebINT ebCAPI ebExecuteW(ebLPEXECUTESTRUCTW lpes,...);

#ifdef EBWIDE
#define ebExecute ebExecuteW
#else
#define ebExecute ebExecuteA
#endif	/* EBWIDE */

ebINT ebAPI ebExecuteVA(ebLPEXECUTESTRUCTA lpes,ebLPCVOID lpArgs);
ebINT ebAPI ebExecuteVW(ebLPEXECUTESTRUCTW lpes,ebLPCVOID lpArgs);

#ifdef EBWIDE
#define ebExecuteV ebExecuteVW
#else
#define ebExecuteV ebExecuteVA
#endif	/* EBWIDE */

ebHSCRIPT ebAPI ebCreateScript(ebHINSTANCE hInstance,ebHCODE hCode,ebLPINT lpError);

ebHSCRIPT ebAPI ebCreateScriptExA(ebHINSTANCE hInstance,ebHCODE hCode,ebLPINT lpError,ebLPSTR lpErrorBuffer,ebINT ErrorBufSz);
ebHSCRIPT ebAPI ebCreateScriptExW(ebHINSTANCE hInstance,ebHCODE hCode,ebLPINT lpError,ebLPWSTR lpErrorBuffer,ebINT ErrorBufSz);
#ifdef EBWIDE
#define ebCreateScriptEx ebCreateScriptExW
#else
#define ebCreateScriptEx ebCreateScriptExA
#endif	/* EBWIDE */

void ebAPI ebStartThread(ebHTHREAD hThread);
ebBOOL ebAPI ebDestroyScript(ebHSCRIPT hScript);

ebHTHREAD ebAPI ebCreateThreadA(ebHSCRIPT hScript,ebLPENTRYINFOA lpei,ebINT iThreadExtra,ebLPINT lpError);
ebHTHREAD ebAPI ebCreateThreadW(ebHSCRIPT hScript,ebLPENTRYINFOW lpei,ebINT iThreadExtra,ebLPINT lpError);
#ifdef EBWIDE
#define ebCreateThread ebCreateThreadW
#else
#define ebCreateThread ebCreateThreadA
#endif	/* EBWIDE */

void ebAPI ebDestroyThread(ebHTHREAD hThread);

void ebAPI ebVersionA(ebLPSTR lpDest);	/* returns string: major.minor.rev */
void ebAPI ebVersionW(ebLPWSTR lpDest);	/* returns string: major.minor.rev */
#ifdef EBWIDE
#define ebVersion ebVersionW
#else
#define ebVersion ebVersionA
#endif	/* EBWIDE */

long ebAPI ebGetExtDataExA(ebHINSTANCE hInstance,ebLPCSTR lpName);
long ebAPI ebGetExtDataExW(ebHINSTANCE hInstance,ebLPCWSTR lpName);

#ifdef EBWIDE
#define ebGetExtDataEx ebGetExtDataExW
#else
#define ebGetExtDataEx ebGetExtDataExA
#endif	/* EBWIDE */

long ebAPI ebSetExtData(ebHOBJECT hObject,long lParam);
long ebAPI ebGetExtData(ebHOBJECT hObject);
void ebAPI ebFreePtr(ebLPVOID lpSomething);

#define EO_FIRSTSCRIPT		1	/* get first script */
#define EO_NEXTSCRIPT		2	/* get next script, given a script */
#define EO_FIRSTTHREAD		3	/* get first thread */
#define EO_NEXTTHREAD		4	/* get next thread, given a thread */
ebHOBJECT ebAPI ebEnumObject(ebHOBJECT hInst,ebINT nCmd);

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Disassembler (not for distribution)
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

ebLPSTR ebAPI ebDecodeA(ebHINSTANCE hInst,ebLPCSTR lpText,const ebHCODE hCode);
ebLPWSTR ebAPI ebDecodeW(ebHINSTANCE hInst,ebLPCWSTR lpText,const ebHCODE hCode);

#ifdef EBWIDE
#define ebDecode ebDecodeW
#else
#define ebDecode ebDecodeA
#endif	/* EBWIDE */

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Routines for dynamic prototype creation
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

ebDECLARE_HANDLE32(ebHPROTO);

ebHPROTO ebAPI ebProtoBeginA(void);
ebHPROTO ebAPI ebProtoBeginW(void);

#ifdef EBWIDE
#define ebProtoBegin ebProtoBeginW
#else
#define ebProtoBegin ebProtoBeginA
#endif	/* EBWIDE */

typedef struct tagebPROTOPARAMA {
	ebWORD wType;				/* type of this parameter (one of the TYP_* values) */
	ebLPSTR lpExtType;		/* extended type for this parameter (structure or app object name) */
	ebLPSTR lpArgName;		/* name of the argument (if PROTO_NAMEDPARMS bit is set) */
} ebPROTOPARAMA,ebFAR *ebLPPROTOPARAMA;

typedef struct tagebPROTOPARAMW {
	ebWORD wType;				/* type of this parameter (one of the TYP_* values) */
	ebLPWSTR lpExtType;		/* extended type for this parameter (structure or app object name) */
	ebLPWSTR lpArgName;		/* name of the argument (if PROTO_NAMEDPARMS bit is set) */
} ebPROTOPARAMW,ebFAR *ebLPPROTOPARAMW;

#ifdef EBWIDE
typedef ebPROTOPARAMW ebPROTOPARAM;
typedef ebLPPROTOPARAMW ebLPPROTOPARAM;
#else
typedef ebPROTOPARAMA ebPROTOPARAM;
typedef ebLPPROTOPARAMA ebLPPROTOPARAM;
#endif	/* EBWIDE */

ebBOOL ebAPI ebProtoEnd(ebHPROTO hp,ebLPVOID ebFAR *lplpProto,ebLPDWORD lpdwSize);
void ebCAPI ebProtoAddFunc(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwId,_ebWORD wType,ebLPCTSTR lpExtType,_ebWORD wminargs,_ebWORD wmaxargs,...);
void ebAPI ebProtoAddFuncV(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwId,_ebWORD wType,ebLPCTSTR lpExtType,_ebWORD wminargs,_ebWORD wmaxargs,ebLPCVOID lpParams);
void ebCAPI ebProtoAddCmd(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwId,_ebWORD wminargs,_ebWORD wmaxargs,...);
void ebAPI ebProtoAddCmdV(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwId,_ebWORD wminargs,_ebWORD wmaxargs,ebLPCVOID lpParams);
void ebCAPI ebProtoAddInline(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwId,_ebWORD wminargs,_ebWORD wmaxargs,...);
void ebAPI ebProtoAddInlineV(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwId,_ebWORD wminargs,_ebWORD wmaxargs,ebLPCVOID lpParams);
void ebCAPI ebProtoAddEntryCmd(ebHPROTO hp,ebLPCTSTR lpName,_ebWORD wminargs,_ebWORD wmaxargs,...);
void ebAPI ebProtoAddEntryCmdV(ebHPROTO hp,ebLPCTSTR lpName,_ebWORD wminargs,_ebWORD wmaxargs,ebLPCVOID lpParams);
void ebAPI ebProtoAddEntryCmdExV(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,_ebWORD wminargs,_ebWORD wmaxargs,ebLPCVOID lpParams);
void ebCAPI ebProtoAddEntryFunc(ebHPROTO hp,ebLPCTSTR lpName,_ebWORD wType,ebLPCTSTR lpExtType,_ebWORD wminargs,_ebWORD wmaxargs,...);
void ebAPI ebProtoAddEntryFuncV(ebHPROTO hp,ebLPCTSTR lpName,_ebWORD wType,ebLPCTSTR lpExtType,_ebWORD wminargs,_ebWORD wmaxargs,ebLPCVOID lpParams);
void ebAPI ebProtoAddEntryFuncExV(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,_ebWORD wType,ebLPCTSTR lpExtType,_ebWORD wminargs,_ebWORD wmaxargs,ebLPCVOID lpParams);
void ebCAPI ebProtoAddConst(ebHPROTO hp,ebLPCTSTR lpName,_ebWORD wType,ebLPCTSTR lpExtType,...);
void ebAPI ebProtoAddConstV(ebHPROTO hp,ebLPCTSTR lpName,_ebWORD wType,ebLPCTSTR lpExtType,ebLPCVOID lpParams);
void ebAPI ebProtoAddStruct(ebHPROTO hp,ebLPCTSTR lpName);
void ebAPI ebProtoAddStructMember(ebHPROTO hp,ebLPCTSTR lpName,_ebWORD wType,ebLPCTSTR lpExtType);
void ebAPI ebProtoAddObj(ebHPROTO hp,ebLPCTSTR lpName,ebDWORD dwId,ebLPCTSTR lpBasedOn);
void ebAPI ebProtoAddObjEx(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwId,ebLPCTSTR lpBasedOn);
void ebCAPI ebProtoAddObjCmd(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwId,_ebWORD wminargs,_ebWORD wmaxargs,...);
void ebAPI ebProtoAddObjCmdV(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwId,_ebWORD wminargs,_ebWORD wmaxargs,ebLPCVOID lpParams);
void ebCAPI ebProtoAddObjFunc(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwId,_ebWORD wType,ebLPCTSTR lpExtType,_ebWORD wminargs,_ebWORD wmaxargs,...);
void ebAPI ebProtoAddObjFuncV(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwId,_ebWORD wType,ebLPCTSTR lpExtType,_ebWORD wminargs,_ebWORD wmaxargs,ebLPCVOID lpParams);
void ebAPI ebProtoAddObjProp(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwSetID,ebDWORD dwGetID,_ebWORD wType,ebLPCTSTR lpExtType);
void ebAPI ebProtoSetModuleName(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName);
void ebCAPI ebProtoAddObjPropSet(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwID,_ebWORD wType,ebLPCTSTR lpExtType,_ebWORD wminargs,_ebWORD wmaxargs,...);
void ebAPI ebProtoAddObjPropSetV(ebHPROTO hp,_ebWORD wFlags,ebLPCTSTR lpName,ebDWORD dwID,_ebWORD wType,ebLPCTSTR lpExtType,_ebWORD wminargs,_ebWORD wmaxargs,ebLPCVOID lpParams);

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Extension APIs
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

#define ebTRUE		-1				/* BasicScript value True */
#define ebFALSE	0				/* BasicScript value False */

/* structure defintion for arrays */
typedef struct tagebDIMENSION {
	short wUpper;					/* upper bound of the dimension */
	short wLower;					/* lower bound of the dimension */
} ebDIMENSION,ebFAR *ebLPDIMENSION;

/* (A)rray (F)lags */
#define	AF_FIXED		0x01		/* fixed cannot be redimensioned */

typedef struct tagebARRAY {
	unsigned short wType;	 	/* Array of type */
	unsigned short wExtType; 	/* Symbol index for wType for USERDEF and OBJECT */
	unsigned short wSz;			/* element size 2 -Integer 4-Long */
	unsigned short wInUseCnt;	/* in use count - prevents redims when non-zero */
	ebBYTE bFlags;					/* flags for fixed/dynamic struct/normal */
	ebBYTE bNumDims;				/* number of dimensions */
	ebDIMENSION Dim[1];			/* Maximum number of dimensions (up to 60 of them) */
} ebARRAY,ebFAR *ebLPARRAY;
#define ebARRAYSZ (sizeof(ebARRAY) - sizeof(ebDIMENSION))

#ifdef SCURRENCY_DEFINED
/* these defines for for internal use only */
typedef SCURRENCY ebCURRENCY;
typedef LPSCURRENCY ebLPCURRENCY;
#else
/* normal definition of currency */
typedef struct tagebCURRENCY {
#ifdef ebLITTLE_ENDIAN
	ebDWORD lo;									/* low 32-bits of currency value */
	ebLONG hi;									/* high 32-bits of currency value */
#endif	/* ebLITTLE_ENDIAN */
#ifdef ebBIG_ENDIAN
	ebLONG hi;									/* high 32-bits of currency value */
	ebDWORD lo;									/* low 32-bits of currency value */
#endif	/* ebBIG_ENDIAN */
} ebCURRENCY,ebFAR *ebLPCURRENCY;
#endif	/* SCURRENCY_DEFINED */

#define VF_JUSTCONVERTED	0x4000		/* we JUST converted to this type */
#define VF_FIXEDTYPE			0x0001		/* the variant type cannot be changed */

typedef struct tagebVARIANT {
	ebWORD Type;	 		/* Type of this variant (one of the TYP_* identifiers */
	ebWORD ExtType; 		/* Extended type for application-defined objects */
	ebWORD Flags;	 		/* Reserved */
	ebWORD Reserved;		/* Reserved */
	union {					/* The member used below depends on the Type member */
		short i;	 			/* Integer */
		ebLONG l;	 		/* Long */
		short b;				/* Boolean */
		double d;			/* Double */
		float s;			  	/* Single */
		float f;	 			/* Single */
		double date;		/* Date */
		ebHSUB h;			/* String */
		ebDWORD object; 	/* Object */
		ebDWORD o;  		/* Object */
		ebHSUB hString;	/* String */
		ebCURRENCY c;		/* Currency */
		ebLPVOID p;			/* reserved */
	} u;
} ebVARIANT,ebFAR *ebLPVARIANT,ebFAR *ebLPCVARIANT;

#define ebARGS ebLPLPVOID		/* argument passed to extension callback */
#define ebMAXPARMS		32		/* maximum number of parameter passed to an extension routine */

/* routines to get and set parameters passed to extensions */
short ebAPI ebGetInt(ebARGS lpArgs,ebINT index);
void ebAPI ebSetInt(ebARGS lpArgs,ebINT index,_short i);
ebBOOL ebAPI ebGetBool(ebARGS lpArgs,ebINT index);
void ebAPI ebSetBool(ebARGS lpArgs,ebINT index,_ebBOOL i);
ebLONG ebAPI ebGetLong(ebARGS lpArgs,ebINT index);
void ebAPI ebSetLong(ebARGS lpArgs,ebINT index,ebLONG l);
float ebAPI ebGetSingle(ebARGS lpArgs,ebINT index);
void ebAPI ebGetSingleEx(ebARGS lpArgs,ebINT index,float ebFAR *lpResult);
void ebAPI ebSetSingle(ebARGS lpArgs,ebINT index,_float f);
void ebAPI ebSetSingleEx(ebARGS lpArgs,ebINT index,float ebFAR *f);
double ebAPI ebGetDouble(ebARGS lpArgs,ebINT index);
void ebAPI ebGetDoubleEx(ebARGS lpArgs,ebINT index,double ebFAR *lpResult);
void ebAPI ebSetDouble(ebARGS lpArgs,ebINT index,_double d);
void ebAPI ebSetDoubleEx(ebARGS lpArgs,ebINT index,double ebFAR *d);
double ebAPI ebGetDate(ebARGS lpArgs,ebINT index);
void ebAPI ebGetDateEx(ebARGS lpArgs,ebINT index,double ebFAR *lpResult);
void ebAPI ebSetDate(ebARGS lpArgs,ebINT index,_double d);
void ebAPI ebSetDateEx(ebARGS lpArgs,ebINT index,double ebFAR *d);
ebCURRENCY ebAPI ebGetCurrency(ebARGS lpArgs,ebINT index);
void ebAPI ebGetCurrencyEx(ebARGS lpArgs,ebINT index,ebLPCURRENCY lpResult);
void ebAPI ebSetCurrency(ebARGS lpArgs,ebINT index,ebCURRENCY c);
void ebAPI ebSetCurrencyEx(ebARGS lpArgs,ebINT index,ebLPCURRENCY lpc);
ebHSUB ebAPI ebGetString(ebARGS lpArgs,ebINT index);
void ebAPI ebSetString(ebARGS lpArgs,ebINT index,_ebHSUB hStr);
ebDWORD ebAPI ebGetObject(ebARGS lpArgs,ebINT index);
void ebAPI ebSetObject(ebARGS lpArgs,ebINT index,ebDWORD dwObject);
ebLPVOID ebAPI ebGetStruct(ebARGS lpArgs,ebINT index);
ebHSUB ebAPI ebGetArray(ebARGS lpArgs,ebINT index);
ebVARIANT ebAPI ebGetVariant(ebARGS lpArgs,ebINT index);
void ebAPI ebGetVariantEx(ebARGS lpArgs,ebINT index,ebLPVARIANT lpResult);
void ebAPI ebSetVariant(ebARGS lpArgs,ebINT index,ebLPVARIANT lpVariant);

ebWORD ebAPI ebGetAppObjExtTypeA(ebHOBJECT hObject,ebLPCSTR lpName,ebLPVOID lpReserved);
ebWORD ebAPI ebGetAppObjExtTypeW(ebHOBJECT hObject,ebLPCWSTR lpName,ebLPVOID lpReserved);

#ifdef EBWIDE
#define ebGetAppObjExtType ebGetAppObjExtTypeW
#else
#define ebGetAppObjExtType ebGetAppObjExtTypeA
#endif	/* EBWIDE */

#ifdef ebHAVE_OLE

/*
 * OLE 2.0 automation is defined on this platform
 */

#define ebGetOleObject(lpArgs,index) (ebDWORD)ebGetLong((lpArgs),(index))
#define ebSetOleObject(lpArgs,index,l) ebSetLong((lpArgs),(index),(ebDWORD)(l))
ebDWORD ebAPI ebCreateOleId(ebHOBJECT hObject,ebLPDISPATCH lpDispatch);
ebDWORD ebAPI ebCreateOleIdEx(ebHOBJECT hObject,ebLPDISPATCH lpDispatch,ebLCID lcid,_ebBOOL isUnicode);
void ebAPI ebFreeOleId(ebHOBJECT hObject, ebDWORD dwId);
ebLPDISPATCH ebAPI ebGetDispatch(ebHOBJECT hObject,ebDWORD dwId);

#endif	/* ebHAVE_OLE */

ebHSUB ebAPI ebAllocBlk(ebHOBJECT hObject,ebUINT wSize);
void ebAPI ebFreeBlk(ebHOBJECT hObject,_ebHSUB hBlk);
ebLPVOID ebAPI ebLockBlk(ebHOBJECT hObject,_ebHSUB hBlk);
void ebAPI ebUnlockBlk(ebHOBJECT hObject,_ebHSUB hBlk);
ebBOOL ebAPI ebReAllocBlk(ebHOBJECT hObject,_ebHSUB hBlk,ebUINT wNewSize);

ebLPSTR ebAPI ebLockStringA(ebHOBJECT hObject,_ebHSUB hStr);
ebLPWSTR ebAPI ebLockStringW(ebHOBJECT hObject,_ebHSUB hStr);

#ifdef EBWIDE
#define ebLockString ebLockStringW
#else
#define ebLockString ebLockStringA
#endif	/* EBWIDE */

ebHSUB ebAPI ebCreateStringA(ebHOBJECT hObject,ebLPCSTR lpStr);
ebHSUB ebAPI ebCreateStringW(ebHOBJECT hObject,ebLPCWSTR lpStr);

#ifdef EBWIDE
#define ebCreateString ebCreateStringW
#else
#define ebCreateString ebCreateStringA
#endif	/* EBWIDE */

ebHSUB ebAPI ebCreateStringLenA(ebHOBJECT hObject,ebLPCSTR lpStr,ebWORD wLen);
ebHSUB ebAPI ebCreateStringLenW(ebHOBJECT hObject,ebLPCWSTR lpStr,ebWORD wLen);

#ifdef EBWIDE
#define ebCreateStringLen ebCreateStringLenW
#else
#define ebCreateStringLen ebCreateStringLenA
#endif	/* EBWIDE */

ebHSUB ebAPI ebAllocString(ebHOBJECT hObject,_ebWORD wSz);	/* Obsolete! */

ebHSUB ebAPI ebCreateBinaryString(ebHOBJECT hObject,ebLPVOID lpData,_ebWORD wSize);
ebHSUB ebCAPI ebAllocArray(ebHOBJECT hObject,_ebBOOL isFixed,_ebWORD wType,_ebWORD wExtType,ebINT NumDims,...);
ebHSUB ebAPI ebAllocArrayV(ebHOBJECT hObject,_ebBOOL isFixed,_ebWORD wType,_ebWORD wExtType,ebINT NumDims,ebLPCVOID lpParams);

void ebAPI ebUnlockStringA(ebHOBJECT hObject,_ebHSUB hStr);
void ebAPI ebUnlockStringW(ebHOBJECT hObject,_ebHSUB hStr);

#ifdef EBWIDE
#define ebUnlockString ebUnlockStringW
#else
#define ebUnlockString ebUnlockStringA
#endif	/* EBWIDE */

void ebAPI ebFreeString(ebHOBJECT hObject,_ebHSUB hStr);
ebLPVOID ebAPI ebLockArrayData(ebHOBJECT hObject,const ebLPARRAY lpHdr);
void ebAPI ebUnlockArrayData(ebHOBJECT hObject,const ebLPARRAY lpHdr);
ebINT ebAPI ebRedimArray(ebHOBJECT hObject,_ebHSUB hArray,_ebWORD wNumElements);

#ifdef ebMT
/* Used only with multi-threaded applications */
void ebAPI ebSignal(ebHOBJECT hObject,_ebBOOL isYield);
#else
/* In non multi-threaded environments, use these definitions */
#define ebSignal(hObject,isYield)
#endif	/* ebMT */

ebWORD ebAPI ebStringLen(ebLPCTSTR lpStr);

void ebAPI ebRuntimeErrorA(ebHTHREAD hThread,_ebBOOL isFatal,ebDWORD dwErrNum,ebLPCSTR lpErrorText);
void ebAPI ebRuntimeErrorW(ebHTHREAD hThread,_ebBOOL isFatal,ebDWORD dwErrNum,ebLPCWSTR lpErrorText);

#ifdef EBWIDE
#define ebRuntimeError ebRuntimeErrorW
#else
#define ebRuntimeError ebRuntimeErrorA
#endif	/* EBWIDE */

void ebAPI ebRuntimeErrorExA(ebHTHREAD hThread,_ebBOOL isFatal,ebDWORD dwErrNum,ebLPCSTR lpErrorText,ebLPCSTR lpSource,ebLPCSTR lpHelpFile,ebDWORD dwHelpContext);
void ebAPI ebRuntimeErrorExW(ebHTHREAD hThread,_ebBOOL isFatal,ebDWORD dwErrNum,ebLPCWSTR lpErrorText,ebLPCWSTR lpSource,ebLPCWSTR lpHelpFile,ebDWORD dwHelpContext);

#ifdef EBWIDE
#define ebRuntimeErrorEx ebRuntimeErrorExW
#else
#define ebRuntimeErrorEx ebRuntimeErrorExA
#endif	/* EBWIDE */

void ebAPI ebCheckMathError(ebHTHREAD hThread);

ebINT ebAPI ebFormatA(ebHOBJECT hObject,_ebWORD wType,ebLPVOID lpSource,ebLPCSTR lpFormat,ebLPSTR lpDest,ebINT sz);
ebINT ebAPI ebFormatW(ebHOBJECT hObject,_ebWORD wType,ebLPVOID lpSource,ebLPCWSTR lpFormat,ebLPWSTR lpDest,ebINT sz);

#ifdef EBWIDE
#define ebFormat ebFormatW
#else
#define ebFormat ebFormatA
#endif	/* EBWIDE */

/* (V)ariant (C)onvert constants */
#define VC_NUMBER				0x1000 		/* convert to any number type */
#define VC_NUMBERORSTRING	0x2000		/* convert to any number type or a string */

ebINT ebAPI ebVariantConvert(ebHOBJECT hObject,ebLPVARIANT lpSource,ebLPVARIANT lpDest,_ebWORD wWantType);
void ebAPI ebFreeVariant(ebHOBJECT hObject,ebLPVARIANT lpVariant);

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Debugger APIs
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

#define ebCONTEXT_DONTCARE		0L				/* use whatever context a variable is declared in */
#define ebCONTEXT_PUBLIC		1L				/* context used for public variables */
#define ebCONTEXT_PRIVATE		2L				/* context used for private variables */
#define ebCONTEXT_LOCAL			0xFFFFFFFFL	/* context to generically describe a local variable */

typedef union tagebVARIABLE {
	short i;   					/* Integer */
	ebLONG l;					/* Long */
	short b;						/* Boolean */
	double d;					/* Double (8-byte IEEE value) */
	float s;						/* Single (4-byte IEEE value) */
	float f;						/* Single (4-byte IEEE value) */
	double date;				/* Date */
	ebCURRENCY c;				/* Currency */
	ebHSUB h;					/* String (handle to the string in string space) */
	ebDWORD object;		 	/* Object or application-defined object */
	ebDWORD o;  				/* application-defined object */
	ebHSUB hString;			/* String (handle to block in string space) */
	ebHSUB hArray;				/* Array of anything (handle to block in string space) */
	ebLPVOID lpStruct;  		/* Pointer to user-defined type */
	ebLPVOID lpFixedString;	/* pointer to fixed string in BasicScript's native string format */
	ebVARIANT v;				/* Variant */

#ifdef ebHAVE_OLE /* OLE Automation only available on these platforms */
	ebLPDISPATCH lpDispatch;	/* OLE 2.0 Automation object */
#endif	/* ebHAVE_OLE */

} ebVARIABLE,ebFAR *ebLPVARIABLE;

#define DI_VERSION	  	1		/* version of the DBGINFO structure */

typedef struct tagebDBGINFO {
	ebWORD wVersion;				/* version of this structure */
	ebWORD wStartLine;			/* start line of current sub or func */
	ebWORD wEndLine;				/* end line of current sub of func */
	ebWORD wCurrent;				/* current line number */
	ebDWORD context;				/* context */
	ebHSCRIPT hScript;			/* which script is executing */
} ebDBGINFO, ebFAR *ebLPDBGINFO;

typedef struct tagebVARIABLEINFOA {
	ebWORD wType;						/* type of the variable (TYP_*) */
	ebWORD wExtType;					/* extended type (for TYP_USERDEF and TYP_OLEOBJECT) */
	ebBOOL isParameter;				/* TRUE if this local variable is passed in */
	ebWORD wReserved1;				/* reserved value */
	ebDWORD dwReserved2;		 		/* reserved value */
	char szName[VARNAMESZ];			/* variable name */
} ebVARIABLEINFOA,ebFAR *ebLPVARIABLEINFOA;

typedef struct tagebVARIABLEINFOW {
	ebWORD wType;						/* type of the variable (TYP_*) */
	ebWORD wExtType;					/* extended type (for TYP_USERDEF and TYP_OLEOBJECT) */
	ebBOOL isParameter;				/* TRUE if this local variable is passed in */
	ebWORD wReserved1;				/* reserved value */
	ebDWORD dwReserved2;		 		/* reserved value */
	ebWCHAR szName[VARNAMESZ];		/* variable name */
} ebVARIABLEINFOW,ebFAR *ebLPVARIABLEINFOW;

#ifdef EBWIDE
typedef ebVARIABLEINFOW ebVARIABLEINFO;
typedef ebLPVARIABLEINFOW ebLPVARIABLEINFO;
#else
typedef ebVARIABLEINFOA ebVARIABLEINFO;
typedef ebLPVARIABLEINFOA ebLPVARIABLEINFO;
#endif	/* EBWIDE */

typedef struct tagebPROCINFOA {
	char szName[VARNAMESZ];			/* name of this procedure */
	ebWORD wType;	  					/* type of this procedure (0 = SUB, 1 = FUNCTION) */
	ebWORD wRetType;  				/* return type (TYP_*) */
	ebWORD wRetExtType;				/* extended type (if applicapable) */
	ebWORD wStartLine;				/* starting line for this routine */
	ebWORD wEndLine;  				/* ending line for this routinr */
	ebDWORD context;  				/* context of this subroutine -- used to identify */
					  						/* when this procedure is in execution context */
	ebHSCRIPT hScript;				/* handle to the script with this procedure, if applicapable */
} ebPROCINFOA,ebFAR *ebLPPROCINFOA;

typedef struct tagebPROCINFOW {
	ebWCHAR szName[VARNAMESZ];		/* name of this procedure */
	ebWORD wType;	  					/* type of this procedure (0 = SUB, 1 = FUNCTION) */
	ebWORD wRetType;  				/* return type (TYP_*) */
	ebWORD wRetExtType;				/* extended type (if applicapable) */
	ebWORD wStartLine;				/* starting line for this routine */
	ebWORD wEndLine;  				/* ending line for this routinr */
	ebDWORD context;  				/* context of this subroutine -- used to identify */
					  						/* when this procedure is in execution context */
	ebHSCRIPT hScript;				/* handle to the script with this procedure, if applicapable */
} ebPROCINFOW,ebFAR *ebLPPROCINFOW;

#ifdef EBWIDE
typedef ebPROCINFOW ebPROCINFO;
typedef ebLPPROCINFOW ebLPPROCINFO;
#else
typedef ebPROCINFOA ebPROCINFO;
typedef ebLPPROCINFOA ebLPPROCINFO;
#endif	/* EBWIDE */

ebINT ebAPI ebLinkA(ebHSCRIPT hScript,ebLPPROCINFOA lpInfo);
ebINT ebAPI ebLinkW(ebHSCRIPT hScript,ebLPPROCINFOW lpInfo);

#ifdef EBWIDE
#define ebLink ebLinkW
#else
#define ebLink ebLinkA
#endif	/* EBWIDE */

ebINT ebAPI ebSetBreakpoint(ebHOBJECT hObject,_ebWORD wLineNo);
ebBOOL ebAPI ebClearBreakpoint(ebHOBJECT hObject,_ebWORD wLineNo);
void ebAPI ebClearBreakpoints(ebHOBJECT hObject);

ebINT ebAPI ebSetBreakpointEx(ebHTHREAD hThread,ebHSCRIPT hScript,_ebWORD wLineNo);
ebBOOL ebAPI ebClearBreakpointEx(ebHTHREAD hThread,ebHSCRIPT hScript,_ebWORD wLineNo);
void ebAPI ebClearBreakpointsEx(ebHTHREAD hThread,ebHSCRIPT hScript);

/* compatibility with old names */
#define ebSetBreakPoint ebSetBreakpoint
#define ebClearBreakPoint ebClearBreakpoint
#define ebClearBreakPoints ebClearBreakpoints

ebBOOL ebAPI ebStepLine(ebHTHREAD hThread);
ebBOOL ebAPI ebTraceLine(ebHTHREAD hThread);
ebBOOL ebAPI ebSetNextLine(ebHTHREAD hThread,_ebWORD wLine);
void ebAPI ebDebugInfo(ebHTHREAD hThread,ebLPDBGINFO lpInfo);
void ebAPI ebConfine(ebHTHREAD hThread,ebHSCRIPT hScript);

ebINT ebAPI ebGetVarValueA(ebHINSTANCE hInst,ebHSCRIPT hScript,ebHTHREAD hThread,ebDWORD context,ebLPCSTR lpExpression,ebLPVARIABLE lpVar,ebLPWORD lpwType,ebLPWORD lpwExtType);
ebINT ebAPI ebGetVarValueW(ebHINSTANCE hInst,ebHSCRIPT hScript,ebHTHREAD hThread,ebDWORD context,ebLPCWSTR lpExpression,ebLPVARIABLE lpVar,ebLPWORD lpwType,ebLPWORD lpwExtType);

#ifdef EBWIDE
#define ebGetVarValue ebGetVarValueW
#else
#define ebGetVarValue ebGetVarValueA
#endif	/* EBWIDE */

ebINT ebAPI ebSetVarValueA(ebHINSTANCE hInst,ebHSCRIPT hScript,ebHTHREAD hThread,ebDWORD context,ebLPCSTR lpExpression,ebLPVARIABLE lpVar);
ebINT ebAPI ebSetVarValueW(ebHINSTANCE hInst,ebHSCRIPT hScript,ebHTHREAD hThread,ebDWORD context,ebLPCWSTR lpExpression,ebLPVARIABLE lpVar);

#ifdef EBWIDE
#define ebSetVarValue ebSetVarValueW
#else
#define ebSetVarValue ebSetVarValueA
#endif	/* EBWIDE */

void ebAPI ebGetMemberArrayHeaderA(ebHOBJECT hObject,ebLPVARIABLEINFOA lpvi,ebLPARRAY lpArray);
void ebAPI ebGetMemberArrayHeaderW(ebHOBJECT hObject,ebLPVARIABLEINFOW lpvi,ebLPARRAY lpArray);

#ifdef EBWIDE
#define ebGetMemberArrayHeader ebGetMemberArrayHeaderW
#else
#define ebGetMemberArrayHeader ebGetMemberArrayHeaderA
#endif	/* EBWIDE */

ebBOOL ebAPI ebGetProcInfoA(ebHOBJECT hObject,ebLPCSTR lpProcName,ebLPPROCINFOA lpProcInfo);
ebBOOL ebAPI ebGetProcInfoW(ebHOBJECT hObject,ebLPCWSTR lpProcName,ebLPPROCINFOW lpProcInfo);

#ifdef EBWIDE
#define ebGetProcInfo ebGetProcInfoW
#else
#define ebGetProcInfo ebGetProcInfoA
#endif	/* EBWIDE */

ebBOOL ebAPI ebGetVarInfoA(ebHOBJECT hObject,ebLPCSTR lpVarName,ebDWORD context,ebLPVARIABLEINFOA lpVarInfo);
ebBOOL ebAPI ebGetVarInfoW(ebHOBJECT hObject,ebLPCWSTR lpVarName,ebDWORD context,ebLPVARIABLEINFOW lpVarInfo);

#ifdef EBWIDE
#define ebGetVarInfo ebGetVarInfoW
#else
#define ebGetVarInfo ebGetVarInfoA
#endif	/* EBWIDE */

ebBOOL ebAPI ebGetMemberInfoA(ebHOBJECT hObject,_ebWORD wExtType,ebLPCSTR lpMemberName,ebLPVARIABLEINFOA lpVarInfo);
ebBOOL ebAPI ebGetMemberInfoW(ebHOBJECT hObject,_ebWORD wExtType,ebLPCWSTR lpMemberName,ebLPVARIABLEINFOW lpVarInfo);

#ifdef EBWIDE
#define ebGetMemberInfo ebGetMemberInfoW
#else
#define ebGetMemberInfo ebGetMemberInfoA
#endif	/* EBWIDE */

ebBOOL ebAPI ebGetObjectInfoA(ebHOBJECT hObject,_ebWORD wExtType,ebLPVARIABLEINFOA lpvi);
ebBOOL ebAPI ebGetObjectInfoW(ebHOBJECT hObject,_ebWORD wExtType,ebLPVARIABLEINFOW lpvi);

#ifdef EBWIDE
#define ebGetObjectInfo ebGetObjectInfoW
#else
#define ebGetObjectInfo ebGetObjectInfoA
#endif	/* EBWIDE */

ebBOOL ebAPI ebGetObjectInfoExA(ebHOBJECT hObject,ebLPCSTR lpType,ebLPVARIABLEINFOA lpvi);
ebBOOL ebAPI ebGetObjectInfoExW(ebHOBJECT hObject,ebLPCWSTR lpType,ebLPVARIABLEINFOW lpvi);

#ifdef EBWIDE
#define ebGetObjectInfoEx ebGetObjectInfoExW
#else
#define ebGetObjectInfoEx ebGetObjectInfoExA
#endif	/* EBWIDE */

ebBOOL ebAPI ebGetStructInfoA(ebHOBJECT hObject,_ebWORD wExtType,ebLPVARIABLEINFOA lpvi);
ebBOOL ebAPI ebGetStructInfoW(ebHOBJECT hObject,_ebWORD wExtType,ebLPVARIABLEINFOW lpvi);

#ifdef EBWIDE
#define ebGetStructInfo ebGetStructInfoW
#else
#define ebGetStructInfo ebGetStructInfoA
#endif	/* EBWIDE */

ebBOOL ebAPI ebGetStructInfoExA(ebHOBJECT hObject,ebLPCSTR lpType,ebLPVARIABLEINFOA lpvi);
ebBOOL ebAPI ebGetStructInfoExW(ebHOBJECT hObject,ebLPCWSTR lpType,ebLPVARIABLEINFOW lpvi);

#ifdef EBWIDE
#define ebGetStructInfoEx ebGetStructInfoExW
#else
#define ebGetStructInfoEx ebGetStructInfoExA
#endif	/* EBWIDE */

typedef void ebNEAR *ebHENUM;		/* handle to enumeration structure */

/* Enumerations routines */
ebHENUM ebAPI ebGetFirstMemberA(ebHOBJECT hObject,_ebWORD wExtType,ebLPVARIABLEINFOA lpvi);
ebHENUM ebAPI ebGetFirstMemberW(ebHOBJECT hObject,_ebWORD wExtType,ebLPVARIABLEINFOW lpvi);

#ifdef EBWIDE
#define ebGetFirstMember ebGetFirstMemberW
#else
#define ebGetFirstMember ebGetFirstMemberA
#endif	/* EBWIDE */

ebBOOL ebAPI ebGetNextMemberA(ebHENUM hEnum,ebLPVARIABLEINFOA lpvi);
ebBOOL ebAPI ebGetNextMemberW(ebHENUM hEnum,ebLPVARIABLEINFOW lpvi);

#ifdef EBWIDE
#define ebGetNextMember ebGetNextMemberW
#else
#define ebGetNextMember ebGetNextMemberA
#endif	/* EBWIDE */

ebHENUM ebAPI ebGetFirstProcA(ebHOBJECT hObject,ebLPPROCINFOA lppi);
ebHENUM ebAPI ebGetFirstProcW(ebHOBJECT hObject,ebLPPROCINFOW lppi);

#ifdef EBWIDE
#define ebGetFirstProc ebGetFirstProcW
#else
#define ebGetFirstProc ebGetFirstProcA
#endif	/* EBWIDE */

ebBOOL ebAPI ebGetNextProcA(ebHENUM hEnum,ebLPPROCINFOA lppi);
ebBOOL ebAPI ebGetNextProcW(ebHENUM hEnum,ebLPPROCINFOW lppi);

#ifdef EBWIDE
#define ebGetNextProc ebGetNextProcW
#else
#define ebGetNextProc ebGetNextProcA
#endif	/* EBWIDE */

ebBOOL ebAPI ebResolve(ebHTHREAD hThread);

ebHENUM ebAPI ebGetFirstUnresProcA(ebHOBJECT hObject,ebLPPROCINFOA lppi);
ebHENUM ebAPI ebGetFirstUnresProcW(ebHOBJECT hObject,ebLPPROCINFOW lppi);

#ifdef EBWIDE
#define ebGetFirstUnresProc ebGetFirstUnresProcW
#else
#define ebGetFirstUnresProc ebGetFirstUnresProcA
#endif	/* EBWIDE */

ebBOOL ebAPI ebGetNextUnresProcA(ebHENUM hEnum,ebLPPROCINFOA lppi);
ebBOOL ebAPI ebGetNextUnresProcW(ebHENUM hEnum,ebLPPROCINFOW lppi);

#ifdef EBWIDE
#define ebGetNextUnresProc ebGetNextUnresProcW
#else
#define ebGetNextUnresProc ebGetNextUnresProcA
#endif	/* EBWIDE */

ebHENUM ebAPI ebGetFirstVarA(ebHOBJECT hObject,ebDWORD context,ebLPVARIABLEINFOA lpvi);
ebHENUM ebAPI ebGetFirstVarW(ebHOBJECT hObject,ebDWORD context,ebLPVARIABLEINFOW lpvi);

#ifdef EBWIDE
#define ebGetFirstVar ebGetFirstVarW
#else
#define ebGetFirstVar ebGetFirstVarA
#endif	/* EBWIDE */

ebBOOL ebAPI ebGetNextVarA(ebHENUM hEnum,ebLPVARIABLEINFOA lpvi);
ebBOOL ebAPI ebGetNextVarW(ebHENUM hEnum,ebLPVARIABLEINFOW lpvi);

#ifdef EBWIDE
#define ebGetNextVar ebGetNextVarW
#else
#define ebGetNextVar ebGetNextVarA
#endif	/* EBWIDE */

ebHENUM ebAPI ebGetFirstCallA(ebHTHREAD hThread,ebLPPROCINFOA pinfo,ebLPWORD lpLineNo);
ebHENUM ebAPI ebGetFirstCallW(ebHTHREAD hThread,ebLPPROCINFOW pinfo,ebLPWORD lpLineNo);

#ifdef EBWIDE
#define ebGetFirstCall ebGetFirstCallW
#else
#define ebGetFirstCall ebGetFirstCallA
#endif	/* EBWIDE */

ebBOOL ebAPI ebGetNextCallA(ebHENUM hEnum,ebLPPROCINFOA pinfo,ebLPWORD lpLineNo);
ebBOOL ebAPI ebGetNextCallW(ebHENUM hEnum,ebLPPROCINFOW pinfo,ebLPWORD lpLineNo);

#ifdef EBWIDE
#define ebGetNextCall ebGetNextCallW
#else
#define ebGetNextCall ebGetNextCallA
#endif	/* EBWIDE */

void ebAPI ebEnumClose(ebHENUM hEnum);
ebHENUM ebAPI ebGetFirstBreakpoint(ebHOBJECT hObject,ebLPWORD lpwLineNo);
ebHENUM ebAPI ebGetFirstBreakpointEx(ebHTHREAD hThread,ebHSCRIPT hScript,ebLPWORD lpwLineNo);
ebBOOL ebAPI ebGetNextBreakpoint(ebHENUM hEnum,ebLPWORD lpwLineNo);

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Support for picture and picture button controls (where supported)
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

#define PICTURE_CLASS_NAME		ebOEM ebPLATFORM ebVERSION ebTEXT("SSC:PICTURE")
#define PICTBTN_CLASS_NAME		ebOEM ebPLATFORM ebVERSION ebTEXT("SSC:PICTBTN")

#if defined(EBWIN) || defined(EBWIN32)
#define ebMETAFILE 256
#define RT_METAFILE	MAKEINTRESOURCE(ebMETAFILE)
#endif	/* EBWIN */

#endif	/* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * File header for compiled files (used only in sample applications)
 * ----------------------------------------------------------------------- */
#ifndef RC_INVOKED

#define FH_VERSION		3							/* version number of file header */
#define FH_ID				(('E' << 8) | 'B')	/* ID of files with compiled code */

typedef struct tagebFILEHEADER {
	unsigned short id;	 		/* ('E' << 8) | 'B' */
	unsigned short wVersion; 	/* version for this file (use FH_VERSION) */
	ebDWORD dwCodeSz;	 			/* size of the code */
	ebDWORD dwScriptSz;			/* script size (0 if there is no script) */
	ebDWORD dwCode;				/* seek position of the code from start of file */
	ebDWORD dwScript;				/* seek position of script from start of file */
} ebFILEHEADER,ebFAR *ebLPFILEHEADER;

#ifdef WANT_PACK
/* set packing back to the default for those who use this */
#pragma pack()
#endif	/* WANT_PACK */

#endif /* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Prototype table defines
 * ----------------------------------------------------------------------- */
#define MIN_DATE			-657434.99998264	/* smallest date representable by BasicScript */
#define MAX_DATE			2958465.99998843	/* largest date representable by BasicScript */

#define TYP_ARRAY				0x4000	/* set if this parameter is an array */
#define TYP_MODSPARM			0x0400	/* set if this parameter can be modified by the caller */
#define TYP_FIXEDLENGTH		0x2000	/* set for fixed-length strings */
#define TYP_FIXEDSTRING		(TYP_FIXEDLENGTH | TYP_STRING)
#define TYP_OLETYPE			0x0100	/* set if this OLE parameter contains an explicit type */
#define TYP_OLEOBJECTTYPE	(TYP_OLEOBJECT | TYP_OLETYPE)

#define TYP_EMPTY			0x0000		/* Empty */
#define TYP_NULL			0x0001		/* Null */
#define TYP_INTEGER		0x0002		/* Integer */
#define TYP_LONG			0x0003		/* Long */
#define TYP_SINGLE		0x0004		/* Single */
#define TYP_DOUBLE		0x0005		/* Double */
#define TYP_CURRENCY		0x0006		/* Currency (currently unsupported) */
#define TYP_DATE			0x0007		/* Date */
#define TYP_STRING		0x0008		/* String */
#define TYP_OLEOBJECT	0x0009		/* application-defined object */
#define TYP_ERROR			0x000A		/* Error (currently unsupported) */
#define TYP_BOOLEAN		0x000B		/* Boolean */
#define TYP_VARIANT		0x000C		/* Variant */
#define TYP_APPOBJECT	0x000D		/* application-defined object */
#define TYP_DIALOG		0x000E		/* dialog structure */
#define TYP_USERDEF		0x000F		/* user-defined data type (structure) */

#define TYP_TYPEMASK		0x000F		/* used to mask the type (mask off upper bits) */

/* values used for arrays of existing types */
#define TYP_ARRAYINTEGER	(TYP_ARRAY | TYP_INTEGER)		/* array of integers */
#define TYP_ARRAYSTRING		(TYP_ARRAY | TYP_STRING)		/* array of strings */
#define TYP_ARRAYLONG		(TYP_ARRAY | TYP_LONG)			/* array of longs */
#define TYP_ARRAYSINGLE		(TYP_ARRAY | TYP_SINGLE)		/* array of singles */
#define TYP_ARRAYDOUBLE		(TYP_ARRAY | TYP_DOUBLE)		/* array of doubles */
#define TYP_ARRAYBOOLEAN	(TYP_ARRAY | TYP_BOOLEAN)		/* array of booleans */
#define TYP_ARRAYDATE		(TYP_ARRAY | TYP_DATE)			/* array of dates */
#define TYP_ARRAYVARIANT	(TYP_ARRAY | TYP_VARIANT)		/* array of variants */

/* prototype table entry identifiers */
#define PROTO_FUNC			0x0000		/* function */
#define PROTO_CMD				0x0001		/* statement */
#define PROTO_INLINE			0x0003		/* inline statement */
#define PROTO_ENTRYCMD		0x2001		/* Entry point subroutine */
#define PROTO_ENTRYFUNC		0x2000		/* Entry point function */
#define PROTO_DUPFUNC		0x4000		/* specifies that current definition duplicates an earlier function name */
#define PROTO_DUPCMD			0x4001		/* specifies that current definition duplicates an earlier statement name */
#define PROTO_ENDMARK		0xFFFF		/* signifies the end of the prototype table */
#define PROTO_CASESENSE		0x8000		/* or'd with func or cmd to only be recongnized when compare=TRUE */
#define PROTO_CASEINSENSE	0x8200		/* or'd with func or cmd to only be recongnized when compare=FALSE */
#define PROTO_NAMEDPARMS	0x1000		/* or'd with func or cmd or OBJECT_ to indicated named parameters are present */
#define PROTO_PARAMARRAY	0x0800		/* or'd with func or cmd or OBJECT_ to indicated last argument is an ebPROTOPARAM array */

#define OBJECT_COMMAND		0x0001		/* object method command */
#define OBJECT_FUNCTION		0x0002		/* object method function */
#define OBJECT_PROPGET		0x0003		/* object property-get function */
#define OBJECT_PROPSET		0x0004		/* object property-set command */
#define OBJECT_ENDDEF		0x0006		/* indicates the end of an object definition */
#define OBJECT_FLAGS			0x0007		/* Indicates flags follow */
#define OBJECT_CASESENSE	0x8000		/* or'd with func or cmd to only be recongnized when compare=TRUE */
#define OBJECT_CASEINSENSE	0x8200		/* or'd with func or cmd to only be recongnized when compare=FALSE */
#define OBJECT_NOREFRTN		0xFFFF		/* indicates no reference routine for this object */
#define OBJECT_REFNEW		0x0000		/* sent to object ref rtn when a new object is requested */
#define OBJECT_REFINC		0x0001		/* sent to object ref rtn when an object gains additional reference */
#define OBJECT_REFDEC		0x0002		/* sent to object ref rtn when an object loses a reference */
#define OBJECT_DEFAULT		0x4000		/* ORed with OBJECT_PROPGET, OBJECT_PROPSET, OBJECT_FUNCTION for default property and function */

#define OBJECTFLG_HIDDEN	0x0001		/* Indicates that the object is hidden */
#define OBJECTFLG_OLE		0x0002		/* Indicates that the object is synonyn for an OLE object */
#define OBJECTFLG_READ		0x0004		/* Indicates that the OLE object property is read-able */
#define OBJECTFLG_WRITE		0x0008		/* Indicates that the OLE object property is write-able */
#define OBJECTFLG_READWRITE (OBJECTFLG_READ | OBJECTFLG_WRITE)

#define MODULE_NAME			0x0001		/* Indicates that the module name should be changed */

#define PROTO_BEGIN			0x0001		/* marks the start of the prototype block */
#define PROTO_END				0xFFFF		/* marks the end of the prototype block */
#define CONST_BEGIN			0x0002		/* marks the start of the constant block */
#define CONST_END				0xFFFF		/* marks the end of the constant block */
#define STRUCT_BEGIN			0x0003		/* marks the beginning of structure definitions */
#define STRUCT_END			0xFFFF		/* marks the end of structure definitions */
#define OBJECT_BEGIN			0x0004		/* marks the start of object definitions */
#define OBJECT_END			0xFFFF		/* marks the end of object definitions */
#define MODULE_BEGIN			0x0005		/* marks the start of a module definition */
#define MODULE_END			0xFFFF		/* marks the end of a module definition */
#define TABLE_END				0xFFFF		/* signifies the end of all the lists */

/* --------------------------------------------------------------------------
 * Error message defines
 * ----------------------------------------------------------------------- */
#define ERRBUFSIZE							256	/* maximum size of an error message string */

/* Visual Basic errors */
#define ERR_RETNOGOSUB						3		/* Return without GoSub */
#define ERR_ILLEGALFUNCTIONCALL			5		/* Invalid procedure call */
#define ERR_OVERFLOW							6		/* Overflow */
#define ERR_OUTOFMEMORY						7		/* Out of memory */
#define ERR_INDXOUTOFBOUNDS				9		/* Subscript out of range */
#define ERR_DUPLICATEDEFINITION			10		/* This array is fixed or temporarily locked */
#define ERR_ARRAYLOCKED						10		/* This array is fixed or temporarily locked */
#define ERR_DIVIDE0							11		/* Division by zero */
#define ERR_TYPEMISMATCH					13		/* Type mismatch */
#define ERR_OUTOFSTRINGSPACE				14		/* Out of string space */
#define ERR_CANCEL							18 	/* User interrupt occurred */
#define ERR_RESUMENOERR						20		/* Resume without error */
#define ERR_DIALOG_NEEDS_BUTTON			26		/* Dialog needs End Dialog or push button */
#define ERR_OUTOFSTACKSPACE				28		/* Out of stack space */
#define ERR_SUBFUNCNOTDEFINED				35		/* Sub or Function not defined */
#define ERR_UNABLETOLOADDLL				48		/* Error in loading DLL */
#define ERR_BADDLLCALL						49		/* Bad DLL calling convention */
#define ERR_INTERNAL							51		/* Internal error */
#define ERR_BADFILENUMBER					52		/* Bad file name or number */
#define ERR_FILENOTFOUND					53		/* File not found */
#define ERR_BADFILEMODE						54		/* Bad file mode */
#define ERR_FILEALREADYOPEN				55		/* File already open */
#define ERR_DISKERROR						57		/* Device I/O error */
#define ERR_FILEALREADYEXISTS				58		/* File already exists */
#define ERR_BADRECORDLENGTH				59		/* Bad record length */
#define ERR_DISKFULL							61		/* Disk full */
#define ERR_INPUTPASTEOF					62		/* Input past end of file */
#define ERR_BADRECORDNUMBER				63		/* Bad record number */
#define ERR_TOOMANYFILES					67		/* Too many files */
#define ERR_INVALIDDRIVE					68		/* Device unavailable */
#define ERR_ACCESSDENIED					70		/* Permission denied */
#define ERR_DRIVENOTREADY					71		/* Disk not ready */
#define ERR_CANTRENAME						74		/* Can't rename with different drive */
#define ERR_FILEACCESSERROR				75		/* Path/File access error */
#define ERR_PATHNOTFOUND					76		/* Path not found */
#define ERR_OBJECTVARIABLENOTSET			91		/* Object variable or With block variable not set */
#define ERR_FORLOOPUNINITIALIZED			92		/* For loop not initialized */
#define ERR_PATTERNINVALID					93		/* Invalid pattern string */
#define ERR_INVALIDUSEOFNULL				94		/* Invalid use of Null */
#define ERR_TOO_MANY_DIALOGS				139 	/* Only one user dialog may be up at any time */
#define ERR_CANTFINDCONTROL				140 	/* Dialog control identifier does not match any current control */
#define ERR_BAD_DLG_STATEMENT				141 	/* The %s statement is not available on this dialog control type */
#define ERR_CANT_OPERATE_FOCUS			143 	/* The dialog control with the focus may not be disabled or hidden */
#define ERR_CANT_SET_FOCUS					144 	/* Focus may not be set to a hidden or disabled control */
#define ERR_CONTROL_ALREADY_DEFINED		150 	/* Dialog control identifier is already defined */
#define ERR_DIALOGSTATEMENTCONTEXT		163 	/* This statement can only be used when a user dialog is active */
#define ERR_NOTIMER							260 	/* No timer available */
#define ERR_TOOMANYCHANNELS				281 	/* No more DDE channels */
#define ERR_CANTINITIATE					282 	/* No foreign application responded to a DDE initiate */
#define ERR_TOOMANYRESPONSES				283 	/* Multiple applications responded to a DDE initiate */
#define ERR_APPNOTACCEPT					285 	/* Foreign application won't perform DDE method or operation */
#define ERR_DDETIMEOUT						286 	/* Timeout while waiting for DDE response */
#define ERR_DDEESCAPE						287 	/* User pressed Escape key during DDE operation */
#define ERR_APPBUSY							288 	/* Destination is busy */
#define ERR_NODATA							289 	/* Data not provided in DDE operation */
#define ERR_DATAWRONGFORMAT				290 	/* Data in wrong format */
#define ERR_HOSTQUIT							291 	/* Foreign application quit */
#define ERR_CONVCHANGED						292 	/* DDE conversation closed or changed */
#define ERR_CANTPOST							295 	/* Message queue filled; DDE message lost */
#define ERR_NODDEML							298 	/* DDE requires ddeml.dll */
#define ERR_OLEInvalidPropertyValue		380	/* Invalid property value */
#define ERR_OLEPropertyMethodNotFound	423	/* Property or method not found */
#define ERR_OLEObjectRequred				424	/* Object required */
#define ERR_OLECreateFailed				429 	/* OLE Automation server can't create object */
#define ERR_OLENotAutomationObject		430 	/* Class doesn't support OLE Automation */
#define ERR_OLECantLoadFile				431 	/* OLE Automation server cannot load file */
#define ERR_OLEFileOrObjectNameError	432 	/* File name or class name not found during OLE Automation operation */
#define ERR_OLENoPropOrMethod				438 	/* Object doesn't support this property or method */
#define ERR_OLEGeneric						440 	/* OLE Automation error */
#define ERR_OLEConnectionLost				442	/* Connection to type library or object library for remote process has been lost. Press OK for dialog to remove reference. */
#define ERR_OLENoDefaultValue				443 	/* Object does not have a default value */
#define ERR_OLEObjectNotSupportAction	445	/* Object doesn't support this action */
#define ERR_OLENamedArgsNotSupported	446	/* Object doesn't support named arguments */
#define ERR_OLELocaleNotSupported		447	/* Object doesn't support current locale setting */
#define ERR_OLECantFindNamedArgument	448	/* Named argument not found */
#define ERR_OLEArgumentNotOptional		449	/* Argument not optional */
#define ERR_OLEWrongNumArgsOrBadProp	450	/* Wrong number of arguments or invalid property assignment */
#define ERR_OLEObjectNotCollection		451	/* Object not a collection */
#define ERR_INVALIDORDINAL					452	/* Invalid ordinal */
#define ERR_CANTFINDDLLFUNC				453	/* Specified DLL function not found */
#define ERR_CANTFINDCODERESOURCE			454	/* Code resource not found */
#define ERR_CODERESOURCELOCKERROR		455	/* Code resource lock error */
#define ERR_INVALIDCLIPBOARDFORMAT		460 	/* Invalid Clipboard format */
#define ERR_INVALIDPICTURE					481	/* Invalid picture */
#define ERR_CANTEMPTYCLIPBOARD			520 	/* Can't empty clipboard */
#define ERR_CANTOPENCLIPBOARD				521 	/* Can't open clipboard */
#define ERR_OLESetNotOnCollections		600 	/* Set value not allowed on collections */
#define ERR_OLEGetNotOnCollections		601 	/* Get value not allowed on collections */

#define ERR_ODBC_SQLALLOCENVFAILURE		603 	/* ODBC - SQLAllocEnv failure */
#define ERR_ODBC_SQLALLOCCONFAILURE		604 	/* ODBC - SQLAllocConnect failure */
#define ERR_ODBC_SQLFREECONNECT			608 	/* ODBC - SQLFreeConnect error */
#define ERR_ODBC_SQLALLOCSTMTFAILURE	610 	/* ODBC - SQLAllocStmt failure */
#define ERR_ODBC_OPERATIONCANCELED		3059	/* ODBC - Operation canceled by user */
#define ERR_ODBC_INVALIDSQLSTATEMENT	3129	/* Invalid SQL statement; expected 'DELETE','INSERT','PROCEDURE','SELECT', or 'UPDATE' */
#define ERR_ODBC_CALLFAILED				3146	/* ODBC -- call failed. */
#define ERR_ODBC_CONNECTIONFAILED		3148	/* ODBC -- connection failed. */
#define ERR_ODBC_INVALIDDBID				3276	/* Invalid database ID */

/* BasicScript-specific errors */
#define ERR_WRONGVERSION					800 	/* Incorrect Windows version */
#define ERR_WRONGDIMENSION					801 	/* Too many dimensions */
#define ERR_CANTFINDWINDOW					802 	/* Can't find window */
#define ERR_BADMENUITEM						803 	/* Can't find menu item */
#define ERR_2JOURNALS						804 	/* Another queue is being flushed */
#define ERR_BADCHILD							805 	/* Can't find control */
#define ERR_INVALIDCHANNEL					806 	/* Bad channel number */
#define ERR_DATANOTAVAILABLE				807 	/* Requested data not available */
#define ERR_CANTCREATEPOPUP				808 	/* Can't create popup menu */
#define ERR_COMMANDFAILED					810 	/* Command failed */
#define ERR_NET_ERROR						811 	/* Network error */
#define ERR_NET_FUNCTIONNOTSUPPORTED	812 	/* Network function not supported */
#define ERR_NET_BADPASSWORD				813 	/* Bad password */
#define ERR_NET_ACCESSDENIED				814 	/* Network access denied */
#define ERR_NET_BUSY							815 	/* Network function busy */
#define ERR_QUEOVERFLOW						816 	/* Queue overflow */
#define ERR_TOOMANYCONTROLS				817 	/* Too many dialog controls */
#define ERR_CANTFINDITEM					818 	/* Can't find listbox/combobox item */
#define ERR_CONTROLDISABLED				819 	/* Control is disabled */
#define ERR_WINDOWDISABLED					820 	/* Window is disabled */
#define ERR_CANTWRITEINI					821 	/* Can't write to INI file */
#define ERR_CANTREADINI						822 	/* Can't read from INI file */
#define ERR_SOURCETARGETSAME				823 	/* Can't copy file onto itself */
#define ERR_OLEUnknownObjectName			824 	/* OLE Automation unknown object name	 */
#define ERR_REDIMFIXEDARRAY				825 	/* Redimension of a fixed array */
#define ERR_CANTLOADEXTENSION				826 	/* Can't load and initialize extension */
#define ERR_CANTFINDEXTENSION				827 	/* Can't find extension */
#define ERR_UNSUPPORTED						828 	/* Unsupported function or statement */
#define ERR_ODBC_NODRIVER					829	/* Can't find ODBC libraries */
#define ERR_OLENonArray						830 	/* OLE Automation Lbound or Ubound on non-Array value */
#define ERR_INVALIDDLGPROC					831	/* Incorrect definition for dialog procedure */
#define ERR_INCORRECTNUMARGS				832	/* Incorrect number of arguments for intermodule call */
#define ERR_OLEObjectNotExist				833 	/* OLE Automation object does not exist */
#define ERR_OLEAutoLinkFailed				834 	/* Access to OLE Automation object denied */
#define ERR_OLEInitialize					835 	/* OLE initialization error */
#define ERR_OLEUnsupportedType			836 	/* OLE Automation method returned unsupported type */
#define ERR_OLENoReturnValue				837 	/* OLE Automation method did not return a value */
#define ERR_OLERPCConnectionTerminated	838	/* OLE Automation error - the remote procedure call connection terminated */
#define ERR_OLERPCServerUnavailable		839  	/* OLE Automation error - the RPC server is unavailable */
#define ERR_OLERPCServerTooBusy			840  	/* OLE Automation error - the RPC server is too busy to complete this operation */
#define ERR_OLERPCCallFailed				841	/* OLE Automation error - the remote procedure call failed */
#define ERR_OLERPCFailedDNE				842  	/* OLE Automation error - the remote procedure call failed and did not execute */
#define ERR_INVALIDDISPLAY					843	/* Unix X Display invalid/security violation  */

/* Java Errors */
#define ERR_JAVA_B2JCONVERTERROR			844	
#define ERR_JAVA_CANTCREATENONOBJECT		845	
#define ERR_JAVA_CANTNEWARRAYS				846
#define ERR_JAVA_CLASSNOTFOUND				847
#define ERR_JAVA_CREATETHREADFAILED			848	
#define ERR_JAVA_ERRORONVMDESTRUCT			849
#define ERR_JAVA_FIELDNOTFOUND				850
#define ERR_JAVA_ILLEGALRETURNTYPE			851
#define ERR_JAVA_INCOMPATIBLERETURNTYPES	852			
#define ERR_JAVA_INITEVENTFAILED			853
#define ERR_JAVA_INSUFFICIENTBUFSPACE		854		
#define ERR_JAVA_INVALIDCLASSSIG			855	
#define ERR_JAVA_LIBMETHNOTFOUND			856	
#define ERR_JAVA_LOADLIBRARYERROR			857	
#define ERR_JAVA_METHODNOTFOUND				858
#define ERR_JAVA_NONAMEDPARAMS				859
#define	ERR_JAVA_OBJECTCREATIONERROR		860		
#define	ERR_JAVA_OBJECTVARIABLENOTSET		861		
#define ERR_JAVA_PROPSNOTSUPPORTED			862	
#define ERR_JAVA_RTSVCSSETUPERROR			863	
#define ERR_JAVA_SENDEVENTERROR				864
#define ERR_JAVA_VERSIONNOTSUPPORTED		865		
#define ERR_JAVA_VMNOTINIT					866
#define ERR_JAVA_CALLMETHODONARRAY			867
#define ERR_JAVA_RTSVCSCANTINITDCTMCALLBK	868
#define ERR_JAVA_CANTREG_NATIVES			869
#define ERR_JAVA_THROWABLE					870
#define ERR_JAVA_TYPENOTSUPPORTED			871
#define ERR_JAVA_J2BASSIGNERROR				872

/* --------------------------------------------------------------------------
 * Recorder APIs
 * ----------------------------------------------------------------------- */
#ifdef EBWIN		/* The Recorder is only available under Windows platform */
#ifndef RC_INVOKED

/* (R)ecorder (F)lags */
#define RF_COLLAPSE			0x0001	/* set if events are reduced */
#define RF_HIGHLEVEL			0x0002	/* set if recording high level statements */
#define RF_MOUSE				0x0004	/* set if mouse messaged being recorded */
#define RF_KEYBOARD			0x0008	/* set if recording the keyboard */
#define RF_MOUSEMOVES		0x0010	/* set if recording mouse movement */
#define RF_UNPRESSEDMOVES	0x0020	/* set if recording unpressed mouse moves */
#define RF_MOUSERELATIVE	0x0040	/* set if recording relative mouse positions */
#define RF_COMMENTS			0x0080	/* set if outputting comments */
#define RF_MENUCOMMAND		0x0100	/* set if only recording a menu command */
#define RF_TIME				0x0200	/* set if recording timing information (only if RF_HIGHLEVEL is off) */

#define RF_PRINTWINDOW		0x8000	/* DEBUG - set if printing window numbers */

#define RF_PASS1				0x0001	/* collapse keyboard/mouse */
#define RF_PASS2				0x0002	/* collapse menu commands */
#define RF_PASS3				0x0004	/* collapse Windows builtin controls */
#define RF_PASS4				0x0008	/* collapse scrolling messages */
#define RF_PASS5				0x0010	/* collapse window commands (maximize, minimize...) */
#define RF_PASS6				0x0020	/* collapse window size/move messages */
#define RF_PASSALL		 	(RF_PASS1 | RF_PASS2 | RF_PASS3 | RF_PASS4 | RF_PASS5 | RF_PASS6)

/* recorder errors */
#define RE_OUTOFMEMORY			1		/* insufficient memory for recording */
#define szPanelLocateMessage	ebOEM ebPLATFORM ebTEXT("_PanelLocate")

extern ebBOOL ebAPI ebStartRecorder(ebHWND hWndParent,ebWORD flags,ebWORD flags2,unsigned msg,ebWORD key1,ebWORD key2,ebWORD key3,ebLPCSTR lpDisabledList,ebCKPROC lpck);
typedef ebBOOL (ebAPI *STARTRTN)(ebHWND hWndParent,ebWORD flags,ebWORD flags2,unsigned msg,ebWORD key1,ebWORD key2,ebWORD key3,ebLPCSTR lpDisabledList,ebCKPROC lpck);

extern HANDLE ebAPI ebStopRecorder(void);
typedef HANDLE (ebAPI *STOPRTN)(void);

extern void ebAPI ebAddExternalText(ebLPCSTR lpText);
extern ebBOOL ebAPI ebPauseRecorder(_ebBOOL isPause);

#endif	/* !RC_INVOKED */

#endif	/* EBWIN */

/* --------------------------------------------------------------------------
 * Debugger Control APIs
 * ----------------------------------------------------------------------- */
#if defined(EBWIN) || defined(EBWIN32)	|| defined(EBOS2) || defined(EBMAC)	|| defined(EBUNIX)

#ifndef RC_INVOKED

#ifdef WANT_PACK
#pragma pack(1)
#endif /* WANT_PACK */

/* (d)ebugger (s)tyles */
#define DS_TOOLBAR	 			0x00000001L		/* include debugger toolbar */
#define DS_STATUSBAR				0x00000002L		/* include debugger status bar */
#define DS_NOWATCHWINDOW		0x00000004L		/* do not include watch window */

/* (E)xecution (S)tates for the debugger */
#define ES_IDLE	  				0	/* script is not executing */
#define ES_SUSPENDED				1	/* script is executing, but paused */
#define ES_EXECUTING				2	/* script is executing (inside ExecuteNext) */

/* (D)isplay (F)ormats for the watch variable list in the debugger */
#define DF_DECIMAL  				0	/* display format is in decimal */
#define DF_HEX						1	/* display format is in hex */

/*
 * The following section defines the debugger control message API. Included
 * are message cracker macros for each debugger control message.
 */

ebHWND ebCAPI ebCreateDebuggerA(ebHWND hWndParent,ebINT x,ebINT y,ebINT width, ebINT height,ebDWORD style,ebWORD id,ebINT iExtra,...);
ebHWND ebCAPI ebCreateDebuggerW(ebHWND hWndParent,ebINT x,ebINT y,ebINT width, ebINT height,ebDWORD style,ebWORD id,ebINT iExtra,...);

#ifdef EBWIDE
#define ebCreateDebugger ebCreateDebuggerW
#else
#define ebCreateDebugger ebCreateDebuggerA
#endif	/* EBWIDE */

ebLRESULT ebAPI ebSendAPIA(ebHWND hWnd,ebMSG Msg,ebWPARAM wParam,ebLPARAM lParam);
ebLRESULT ebAPI ebSendAPIW(ebHWND hWnd,ebMSG Msg,ebWPARAM wParam,ebLPARAM lParam);

#ifdef EBWIDE
#define ebSendAPI ebSendAPIW
#else
#define ebSendAPI ebSendAPIA
#endif	/* EBWIDE */

#ifdef EBOS2
#define ebDestroyDebugger WinDestroyWindow
#endif

#if defined(EBWIN) || defined(EBWIN32)
#define ebDestroyDebugger DestroyWindow
#endif

#if defined(EBUNIX)
#define	ebDestroyDebugger(w)	XtDestroyWidget( (Widget)w )
#endif

#ifdef EBMAC
/*
ebHWND ebCreateDebugger(ebHWND hWndParent, ebINT x, ebINT y, ebINT width, ebINT height, ebDWORD style, _ebWORD id, ebHINSTANCE hInstance);
void ebDestroyDebugger(ebHWND hWnd);

typedef void (*ebMACDEBUGGERCALLBACKPROC)(long beforeAction,ebHWND debuggerHandle);
ebMACDEBUGGERCALLBACKPROC ebAPI ebDebugger_RegisterCallback(ebHWND hWndDebugger,ebMACDEBUGGERCALLBACKPROC lpfnNewCallback);
*/
ebBOOL ebAPI ebDebugger_IsEvent(ebHWND hWnd,const EventRecord *anEvent);
void ebAPI ebDebugger_DoEvent(ebHWND hWnd,const EventRecord *anEvent);

#ifdef NEWMACDBGR /* these functions are defined only in the Mac version with the new editor/debugger */
ebHWND ebAPI ebDebugger_GetWindowHandle(WindowPtr aWindow);
void ebAPI ebDebugger_DoIdle(ebHWND hWnd);
#endif

/*
ebBOOL ebAPI ebDebugger_IsEBWindow(WindowPtr aWindow);
void ebAPI ebDebugger_RegisterFloatWindows(ebHWND hWndDebugger,short floatWindowKind);
*/
#endif /* EBMAC */

#if defined(EBMAC)
extern 	ebLRESULT _ebDebuggerSendAPIA( ebHWND,ebMSG,ebWPARAM,ebLPARAM);
#define	MESSAGEROUTINE	_ebDebuggerSendAPIA
#else	/* !EBUNIX */
#define	MESSAGEROUTINE	ebSendAPI
#endif	/* EBUNIX */

typedef ebBOOL (ebCALLBACK _ebKEYBOARDFILTERPROC)(ebHWND hWnd,ebUINT message,ebWPARAM wParam,ebLPARAM lParam);
typedef _ebKEYBOARDFILTERPROC *ebKEYBOARDFILTERPROC;

typedef long (ebCALLBACK _ebNOTIFICATIONPROC)(ebHWND hWndDebugger,ebINT nCode,ebPARAM1 np1,ebPARAM2 np2,long lPassThrough);
typedef _ebNOTIFICATIONPROC *ebNOTIFICATIONPROC;


/* ebBOOL ebDebugger_SetNext(ebHWND hWnd,ebWORD wLineNo); */
#define DM_SETNEXT					(WM_USER + 12)
#define HANDLE_DM_SETNEXT(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(ebWORD)wParam)
#define FORWARD_DM_SETNEXT(hWnd,wLineNo,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_SETNEXT,(ebWPARAM)(wLineNo),0)
#define ebDebugger_SetNext(hWnd,wLineNo) FORWARD_DM_SETNEXT(hWnd,wLineNo,MESSAGEROUTINE)

/* void ebDebugger_SetWatchWindowHeight(ebHWND hWnd,ebWORD NewHeight); */
#define DM_SETWATCHWINDOWHEIGHT		(WM_USER + 15)
#define HANDLE_DM_SETWATCHWINDOWHEIGHT(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(int)wParam),0L)
#define FORWARD_DM_SETWATCHWINDOWHEIGHT(hWnd,NewHeight,fn) (ebDWORD)(fn)((hWnd),DM_SETWATCHWINDOWHEIGHT,(ebWPARAM)(int)NewHeight,0)
#define ebDebugger_SetWatchWindowHeight(hWnd,NewHeight) FORWARD_DM_SETWATCHWINDOWHEIGHT(hWnd,NewHeight,MESSAGEROUTINE)

/* void ebDebugger_SetThreadExtra(ebHWND hWnd,ebWORD sz); */
#define DM_SETTHREADEXTRA			(WM_USER + 49)
#define HANDLE_DM_SETTHREADEXTRA(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(int)wParam),0L)
#define FORWARD_DM_SETTHREADEXTRA(hWnd,sz,fn) (void)(fn)((hWnd),DM_SETTHREADEXTRA,(ebWPARAM)(int)sz,0)
#define ebDebugger_SetThreadExtra(hWnd,sz) FORWARD_DM_SETTHREADEXTRA(hWnd,sz,MESSAGEROUTINE)

/* ebKEYBOARDFILTERPROC ebDebugger_SetKeyboardFilter(ebHWND hWnd,ebKEYBOARDFILTERPROC lpfnFilter); */
#define DM_SETKEYBOARDFILTER		(WM_USER + 50)
#define HANDLE_DM_SETKEYBOARDFILTER(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebKEYBOARDFILTERPROC)(fn)((hWnd),(ebKEYBOARDFILTERPROC)lParam)
#define FORWARD_DM_SETKEYBOARDFILTER(hWnd,lpfnFilter,fn) (ebKEYBOARDFILTERPROC)(ebDWORD)(fn)((hWnd),DM_SETKEYBOARDFILTER,0,(ebLPARAM)(ebKEYBOARDFILTERPROC)(lpfnFilter))
#define ebDebugger_SetKeyboardFilter(hWnd,lpfnFilter) FORWARD_DM_SETKEYBOARDFILTER(hWnd,lpfnFilter,MESSAGEROUTINE)

/* ebBOOL ebDebugger_Confine(ebHWND hWnd,ebBOOL isConfine); */
#define DM_CONFINE					(WM_USER + 51)
#define HANDLE_DM_CONFINE(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(fn)((hWnd),(_ebBOOL)wParam)
#define FORWARD_DM_CONFINE(hWnd,isConfine,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_CONFINE,(ebWPARAM)(ebBOOL)(isConfine),0L)
#define ebDebugger_Confine(hWnd,isConfine) FORWARD_DM_CONFINE(hWnd,isConfine,MESSAGEROUTINE)

/* ebHSCRIPT ebDebugger_GetScript(ebHWND hWnd,ebBOOL isWantOwnership); */
#define DM_GETSCRIPT					(WM_USER + 52)
#define HANDLE_DM_GETSCRIPT(hWnd,wParam,lParam,fn) (LRESULT)(long)(ebHSCRIPT)(fn)((hWnd),(ebBOOL)(wParam))
#define FORWARD_DM_GETSCRIPT(hWnd,isWantOwnership,fn) (ebHSCRIPT)(fn)((hWnd),DM_GETSCRIPT,(ebWPARAM)(ebBOOL)(isWantOwnership),0)
#define ebDebugger_GetScript(hWnd,isWantOwnership) FORWARD_DM_GETSCRIPT(hWnd,isWantOwnership,MESSAGEROUTINE)

/* void ebDebugger_SetInstance(ebHWND hWnd,ebHINSTANCE hInst); */
#define DM_SETINSTANCE				(WM_USER + 46)
#define HANDLE_DM_SETINSTANCE(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(ebHINSTANCE)lParam),0L)
#define FORWARD_DM_SETINSTANCE(hWnd,hInst,fn) (void)(fn)((hWnd),DM_SETINSTANCE,0,(ebLPARAM)(ebHINSTANCE)(hInst))
#define ebDebugger_SetInstance(hWnd,hInst) FORWARD_DM_SETINSTANCE(hWnd,hInst,MESSAGEROUTINE)

/* void ebDebugger_SetEntry(ebHWND hWnd,ebLPENTRYINFO lpei); */
#define DM_SETENTRY					(WM_USER + 45)
#define HANDLE_DM_SETENTRY(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(ebLPENTRYINFO)lParam),0L)
#define FORWARD_DM_SETENTRY(hWnd,lpei,fn) (void)(fn)((hWnd),DM_SETENTRY,0,(ebLPARAM)(ebLPENTRYINFO)(lpei))
#define ebDebugger_SetEntry(hWnd,lpei) FORWARD_DM_SETENTRY(hWnd,lpei,MESSAGEROUTINE)

/* void ebDebugger_SetDisplayFormat(ebHWND hWnd,ebWORD NewFormat); */
#define DM_SETDISPLAYFORMAT			(WM_USER + 32)
#define HANDLE_DM_SETDISPLAYFORMAT(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(int)(wParam)),0L)
#define FORWARD_DM_SETDISPLAYFORMAT(hWnd,NewFormat,fn) (void)(fn)((hWnd),DM_SETDISPLAYFORMAT,(ebWPARAM)(int)(NewFormat),0)
#define ebDebugger_SetDisplayFormat(hWnd,NewFormat) FORWARD_DM_SETDISPLAYFORMAT(hWnd,NewFormat,MESSAGEROUTINE)

/* void ebDebugger_SetDirty(ebHWND hWnd,ebBOOL isDirty); */
#define DM_SETDIRTY					(WM_USER + 38)
#define HANDLE_DM_SETDIRTY(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(ebBOOL)(wParam)),0L)
#define FORWARD_DM_SETDIRTY(hWnd,isDirty,fn) (void)(fn)((hWnd),DM_SETDIRTY,(ebWPARAM)(ebBOOL)(isDirty),0)
#define ebDebugger_SetDirty(hWnd,isDirty) FORWARD_DM_SETDIRTY(hWnd,isDirty,MESSAGEROUTINE)

/* void ebDebugger_SetCode(ebHWND hWnd,ebHCODE hCode); */
#define DM_SETCODE					(WM_USER + 44)
#define HANDLE_DM_SETCODE(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(ebHCODE)lParam),0L)
#define FORWARD_DM_SETCODE(hWnd,hCode,fn) (void)(fn)((hWnd),DM_SETCODE,0,(ebLPARAM)(ebHCODE)(hCode))
#define ebDebugger_SetCode(hWnd,hCode) FORWARD_DM_SETCODE(hWnd,hCode,MESSAGEROUTINE)

/* ebBOOL ebDebugger_ReplaceSel(ebHWND hWnd,ebLPCTSTR lpText,ebBOOL isSelected); */
#define DM_REPLACESEL				(WM_USER + 30)
#define HANDLE_DM_REPLACESEL(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(ebLPCTSTR)lParam,(ebBOOL)wParam)
#define FORWARD_DM_REPLACESEL(hWnd,lpText,isSelected,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_REPLACESEL,(ebWPARAM)(ebBOOL)(isSelected),(ebLPARAM)(ebLPCTSTR)(lpText))
#define ebDebugger_ReplaceSel(hWnd,lpText,isSelected) FORWARD_DM_REPLACESEL(hWnd,lpText,isSelected,MESSAGEROUTINE)

/* ebBOOL ebDebugger_IsDialogSelected(ebHWND hWnd); */
#define DM_ISDIALOGSELECTED			(WM_USER + 9)
#define HANDLE_DM_ISDIALOGSELECTED(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)(hWnd)
#define FORWARD_DM_ISDIALOGSELECTED(hWnd,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_ISDIALOGSELECTED,0,0L)
#define ebDebugger_IsDialogSelected(hWnd) FORWARD_DM_ISDIALOGSELECTED(hWnd,MESSAGEROUTINE)

/* void ebDebugger_ModifyDialog(ebHWND hWnd,ebBOOL isUseSelectedItem); */
#define DM_MODIFYDIALOG				(WM_USER + 40)
#define HANDLE_DM_MODIFYDIALOG(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(ebBOOL)wParam),0L)
#define FORWARD_DM_MODIFYDIALOG(hWnd,isUseSelectedItem,fn) (void)(fn)((hWnd),DM_MODIFYDIALOG,(ebWPARAM)(ebBOOL)(isUseSelectedItem),0L)
#define ebDebugger_ModifyDialog(hWnd,isUseSelectedItem) FORWARD_DM_MODIFYDIALOG(hWnd,isUseSelectedItem,MESSAGEROUTINE)

/* ebBOOL ebDebugger_InsertDialog(ebHWND hWnd); */
#define DM_INSERTDIALOG				(WM_USER + 11)
#define HANDLE_DM_INSERTDIALOG(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)(hWnd)
#define FORWARD_DM_INSERTDIALOG(hWnd,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_INSERTDIALOG,0,0L)
#define ebDebugger_InsertDialog(hWnd) FORWARD_DM_INSERTDIALOG(hWnd,MESSAGEROUTINE)

/* void ebDebugger_GotoLineDialog(ebHWND hWnd); */
#define DM_GOTOLINEDIALOG			(WM_USER + 39)
#define HANDLE_DM_GOTOLINEDIALOG(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_GOTOLINEDIALOG(hWnd,fn) (void)(fn)((hWnd),DM_GOTOLINEDIALOG,0,0L)
#define ebDebugger_GotoLineDialog(hWnd) FORWARD_DM_GOTOLINEDIALOG(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_GetWord(ebHWND hWnd,ebLPTSTR lpDest,ebUINT maxlen); */
#define DM_GETWORD					(WM_USER + 33)
#define HANDLE_DM_GETWORD(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(ebLPTSTR)(lParam),(ebUINT)(wParam))
#define FORWARD_DM_GETWORD(hWnd,lpDest,maxlen,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_GETWORD,(ebWPARAM)(maxlen),(ebLPARAM)(ebLPTSTR)(lpDest))
#define ebDebugger_GetWord(hWnd,lpDest,maxlen) FORWARD_DM_GETWORD(hWnd,lpDest,maxlen,MESSAGEROUTINE)

/* ebDWORD ebDebugger_GetWatchWindowHeight(ebHWND hWnd); */
#define DM_GETWATCHWINDOWHEIGHT	 	(WM_USER + 16)
#define HANDLE_DM_GETWATCHWINDOWHEIGHT(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(int)(fn)(hWnd)
#define FORWARD_DM_GETWATCHWINDOWHEIGHT(hWnd,fn) (int)(ebDWORD)(fn)((hWnd),DM_GETWATCHWINDOWHEIGHT,0,0L)
#define ebDebugger_GetWatchWindowHeight(hWnd) FORWARD_DM_GETWATCHWINDOWHEIGHT(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_IsSelection(ebHWND hWnd); */
#define DM_ISSELECTION				(WM_USER + 25)
#define HANDLE_DM_ISSELECTION(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)(hWnd)
#define FORWARD_DM_ISSELECTION(hWnd,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_ISSELECTION,0,0L)
#define ebDebugger_IsSelection(hWnd) FORWARD_DM_ISSELECTION(hWnd,MESSAGEROUTINE)

/* void ebDebugger_Pause(ebHWND hWnd); */
#define DM_PAUSE					(WM_USER + 6)
#define HANDLE_DM_PAUSE(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_PAUSE(hWnd,fn) (void)(fn)((hWnd),DM_PAUSE,0,0L)
#define ebDebugger_Pause(hWnd) FORWARD_DM_PAUSE(hWnd,MESSAGEROUTINE)

/* ebHTHREAD ebDebugger_GetThread(ebHWND hWnd,ebBOOL isWantOwnership); */
#define DM_GETTHREAD				(WM_USER + 42)
#define HANDLE_DM_GETTHREAD(hWnd,wParam,lParam,fn) (LRESULT)(long)(ebHTHREAD)(fn)((hWnd),(ebBOOL)(wParam))
#define FORWARD_DM_GETTHREAD(hWnd,isWantOwnership,fn) (ebHTHREAD)(fn)((hWnd),DM_GETTHREAD,(ebWPARAM)(ebBOOL)(isWantOwnership),0L)
#define ebDebugger_GetThread(hWnd,isWantOwnership) FORWARD_DM_GETTHREAD(hWnd,isWantOwnership,MESSAGEROUTINE)

/* ebINT ebDebugger_GetState(ebHWND hWnd); */
#define DM_GETSTATE					(WM_USER + 23)
#define HANDLE_DM_GETSTATE(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(int)(fn)(hWnd)
#define FORWARD_DM_GETSTATE(hWnd,fn) (int)(ebDWORD)(fn)((hWnd),DM_GETSTATE,0,0L)
#define ebDebugger_GetState(hWnd) FORWARD_DM_GETSTATE(hWnd,MESSAGEROUTINE)

/* ebUINT ebDebugger_GetSelText(ebHWND hWnd,ebLPTSTR lpDest,ebUINT maxlen); */
#define DM_GETSELTEXT	 			(WM_USER + 31)
#define HANDLE_DM_GETSELTEXT(hWnd,wParam,lParam,fn) (LRESULT)(ebUINT)(fn)((hWnd),(ebLPTSTR)(lParam),(ebUINT)(wParam))
#define FORWARD_DM_GETSELTEXT(hWnd,lpDest,maxlen,fn) (ebUINT)(fn)((hWnd),DM_GETSELTEXT,(ebWPARAM)(maxlen),(ebLPARAM)(ebLPTSTR)(lpDest))
#define ebDebugger_GetSelText(hWnd,lpDest,maxlen) FORWARD_DM_GETSELTEXT(hWnd,lpDest,maxlen,MESSAGEROUTINE)

/* selection structure used with ebDebugger_SetSel/GetSel APIs */
typedef struct tagebSEL {
	ebUINT wStart;						/* starting offset for the selection */
	ebUINT wEnd;						/* ending offset for the selection */
} ebSEL, ebFAR *ebLPSEL;

/* ebBOOL ebDebugger_GetSel(ebHWND hWnd,ebLPSEL lpSel); */
#define DM_GETSEL					(WM_USER + 8)
#define HANDLE_DM_GETSEL(hWnd,wParam,lParam,fn) (LRESULT)(ebBOOL)(fn)((hWnd),(ebLPSEL)lParam)
#define FORWARD_DM_GETSEL(hWnd,lpSel,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_GETSEL,0,(ebLPARAM)(ebLPSEL)lpSel)
#define ebDebugger_GetSel(hWnd,lpSel) FORWARD_DM_GETSEL(hWnd,lpSel,MESSAGEROUTINE)

/* void ebDebugger_SetSel(ebHWND hWnd,ebBOOL isScrollIntoView,ebLPSEL lpSel); */
#define DM_SETSEL					(WM_USER + 69)
#define HANDLE_DM_SETSEL(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(ebBOOL)wParam,(ebLPSEL)(lParam)),0L)
#define FORWARD_DM_SETSEL(hWnd,isScrollIntoView,lpSel,fn) (void)(fn)((hWnd),DM_SETSEL,(ebWPARAM)(ebBOOL)(isScrollIntoView),(ebLPARAM)(ebLPSEL)lpSel)
#define ebDebugger_SetSel(hWnd,isScrollIntoView,lpSel) FORWARD_DM_SETSEL(hWnd,isScrollIntoView,lpSel,MESSAGEROUTINE)

/* flags used with ebDebugger_Find API */
#define ebFIND_MATCHCASE	0x0001	/* match case */
#define ebFIND_WHOLEWORD	0x0002	/* find whole words only */
#define ebFIND_SELECT		0x0004	/* select the found text */
#define ebFIND_VIEW			0x0008	/* scroll the found text into view */
#define ebFIND_DOWN			0x0010	/* search down */
#define ebFIND_UP				0x0020	/* search up */

/* ebLONG ebDebugger_Find(ebHWND hWnd,ebWORD wFlags,ebLPCTSTR lpText); */
#define DM_FIND						(WM_USER + 29)
#define HANDLE_DM_FIND(hWnd,wParam,lParam,fn) (LRESULT)(ebLONG)(fn)((hWnd),(ebWORD)wParam,(ebLPCTSTR)lParam)
#define FORWARD_DM_FIND(hWnd,wFlags,lpText,fn) (ebLONG)(fn)((hWnd),DM_FIND,(ebWPARAM)(ebWORD)wFlags,(ebLPARAM)(ebLPCTSTR)(lpText))
#define ebDebugger_Find(hWnd,wFlags,lpText) FORWARD_DM_FIND(hWnd,wFlags,lpText,MESSAGEROUTINE)

/* ebDWORD ebDebugger_GetScope(ebHWND hWnd); */
#define DM_GETSCOPE					(WM_USER + 28)
#define HANDLE_DM_GETSCOPE(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(fn)(hWnd)
#define FORWARD_DM_GETSCOPE(hWnd,fn) (ebDWORD)(fn)((hWnd),DM_GETSCOPE,0,0L)
#define ebDebugger_GetScope(hWnd) FORWARD_DM_GETSCOPE(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_GetNextWatch(ebHWND hWnd,ebLPTSTR lpDest,ebINT iMaxLen); */
#define DM_GETNEXTWATCH				(WM_USER + 36)
#define HANDLE_DM_GETNEXTWATCH(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(ebLPTSTR)(lParam),(int)(wParam))
#define FORWARD_DM_GETNEXTWATCH(hWnd,lpDest,iMaxLen,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_GETNEXTWATCH,(ebWPARAM)(int)(iMaxLen),(ebLPARAM)(ebLPTSTR)(lpDest))
#define ebDebugger_GetNextWatch(hWnd,lpDest,iMaxLen) FORWARD_DM_GETNEXTWATCH(hWnd,lpDest,iMaxLen,MESSAGEROUTINE)

/* ebBOOL ebDebugger_GetFirstWatch(ebHWND hWnd,ebLPTSTR lpDest,ebINT iMaxLen); */
#define DM_GETFIRSTWATCH			(WM_USER + 35)
#define HANDLE_DM_GETFIRSTWATCH(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(ebLPTSTR)(lParam),(int)(wParam))
#define FORWARD_DM_GETFIRSTWATCH(hWnd,lpDest,iMaxLen,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_GETFIRSTWATCH,(ebWPARAM)(int)(iMaxLen),(ebLPARAM)(ebLPTSTR)(lpDest))
#define ebDebugger_GetFirstWatch(hWnd,lpDest,iMaxLen) FORWARD_DM_GETFIRSTWATCH(hWnd,lpDest,iMaxLen,MESSAGEROUTINE)

/* ebWORD ebDebugger_GetCurLine(ebHWND hWnd); */
#define DM_GETCURLINE				(WM_USER + 26)
#define HANDLE_DM_GETCURLINE(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebWORD)(fn)(hWnd)
#define FORWARD_DM_GETCURLINE(hWnd,fn) (ebWORD)(ebDWORD)(fn)((hWnd),DM_GETCURLINE,0,0L)
#define ebDebugger_GetCurLine(hWnd) FORWARD_DM_GETCURLINE(hWnd,MESSAGEROUTINE)

/* ebHCODE ebDebugger_GetCode(ebHWND hWnd,ebBOOL isWantOwnership); */
#define DM_GETCODE					(WM_USER + 43)
#define HANDLE_DM_GETCODE(hWnd,wParam,lParam,fn) (LRESULT)(ebHCODE)(fn)((hWnd),(ebBOOL)wParam)
#define FORWARD_DM_GETCODE(hWnd,isWantOwnership,fn) (ebHCODE)(fn)((hWnd),DM_GETCODE,(ebWPARAM)(ebBOOL)(isWantOwnership),0)
#define ebDebugger_GetCode(hWnd,isWantOwnership) FORWARD_DM_GETCODE(hWnd,isWantOwnership,MESSAGEROUTINE)

/* ebBOOL ebDebugger_EnableBreak(ebHWND hWnd,ebBOOL isBreak); */
#define DM_ENABLEBREAK				(WM_USER + 48)
#define HANDLE_DM_ENABLEBREAK(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(ebBOOL)(wParam))
#define FORWARD_DM_ENABLEBREAK(hWnd,isBreak,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_ENABLEBREAK,(ebWPARAM)(isBreak),0L)
#define ebDebugger_EnableBreak(hWnd,isBreak) FORWARD_DM_ENABLEBREAK(hWnd,isBreak,MESSAGEROUTINE)

/* ebBOOL ebDebugger_EditDialog(ebHWND hWnd); */
#define DM_EDITDIALOG				(WM_USER + 10)
#define HANDLE_DM_EDITDIALOG(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)(hWnd)
#define FORWARD_DM_EDITDIALOG(hWnd,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_EDITDIALOG,0,0L)
#define ebDebugger_EditDialog(hWnd) FORWARD_DM_EDITDIALOG(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_DeleteWatch(ebHWND hWnd,ebLPCTSTR lpExpression); */
#define DM_DELETEWATCH	   			(WM_USER + 22)
#define HANDLE_DM_DELETEWATCH(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(ebLPCTSTR)(lParam))
#define FORWARD_DM_DELETEWATCH(hWnd,lpExpression,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_DELETEWATCH,0,(ebLPARAM)(ebLPCTSTR)(lpExpression))
#define ebDebugger_DeleteWatch(hWnd,lpExpression) FORWARD_DM_DELETEWATCH(hWnd,lpExpression,MESSAGEROUTINE)

/* ebBOOL ebDebugger_Compile(ebHWND hWnd,ebBOOL isDisplayError); */
#define DM_COMPILE					(WM_USER + 18)
#define HANDLE_DM_COMPILE(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(ebBOOL)(wParam))
#define FORWARD_DM_COMPILE(hWnd,isDisplayError,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_COMPILE,(ebWPARAM)(isDisplayError),0L)
#define ebDebugger_Compile(hWnd,isDisplayError) FORWARD_DM_COMPILE(hWnd,isDisplayError,MESSAGEROUTINE)

/* ebBOOL ebDebugger_CanUndo(ebHWND hWnd); */
#define DM_CANUNDO					(WM_USER + 24)
#define HANDLE_DM_CANUNDO(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)(hWnd)
#define FORWARD_DM_CANUNDO(hWnd,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_CANUNDO,0,0L)
#define ebDebugger_CanUndo(hWnd) FORWARD_DM_CANUNDO(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_CanDeleteWatch(ebHWND hWnd); */
#define DM_CANDELETEWATCH			(WM_USER + 34)
#define HANDLE_DM_CANDELETEWATCH(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)(hWnd)
#define FORWARD_DM_CANDELETEWATCH(hWnd,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_CANDELETEWATCH,0,0L)
#define ebDebugger_CanDeleteWatch(hWnd) FORWARD_DM_CANDELETEWATCH(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_AddWatch(ebHWND hWnd,ebLPCTSTR lpExpression); */
#define DM_ADDWATCH					(WM_USER + 21)
#define HANDLE_DM_ADDWATCH(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(ebLPCTSTR)(lParam))
#define FORWARD_DM_ADDWATCH(hWnd,lpExpression,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_ADDWATCH,0,(ebLPARAM)(ebLPCTSTR)(lpExpression))
#define ebDebugger_AddWatch(hWnd,lpExpression) FORWARD_DM_ADDWATCH(hWnd,lpExpression,MESSAGEROUTINE)

/* void ebDebugger_CallsDialog(ebHWND hWnd); */
#define DM_CALLSDIALOG				(WM_USER + 41)
#define HANDLE_DM_CALLSDIALOG(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_CALLSDIALOG(hWnd,fn) (void)(fn)((hWnd),DM_CALLSDIALOG,0,0L)
#define ebDebugger_CallsDialog(hWnd) FORWARD_DM_CALLSDIALOG(hWnd,MESSAGEROUTINE)

/* void ebDebugger_ClearAllBreakpoints(ebHWND hWnd); */
#define DM_CLEARALLBREAKPOINTS		(WM_USER + 7)
#define HANDLE_DM_CLEARALLBREAKPOINTS(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_CLEARALLBREAKPOINTS(hWnd,fn) (void)(fn)((hWnd),DM_CLEARALLBREAKPOINTS,0,0L)
#define ebDebugger_ClearAllBreakpoints(hWnd) FORWARD_DM_CLEARALLBREAKPOINTS(hWnd,MESSAGEROUTINE)

/* void ebDebugger_End(ebHWND hWnd); */
#define DM_END						(WM_USER + 19)
#define HANDLE_DM_END(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_END(hWnd,fn) (void)(fn)((hWnd),DM_END,0,0L)
#define ebDebugger_End(hWnd) FORWARD_DM_END(hWnd,MESSAGEROUTINE)

/* void ebDebugger_Start(ebHWND hWnd); */
#define DM_START					(WM_USER + 5)
#define HANDLE_DM_START(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_START(hWnd,fn) (void)(fn)((hWnd),DM_START,0,0L)
#define ebDebugger_Start(hWnd) FORWARD_DM_START(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_SetCursorPos(ebHWND hWnd,ebINT x,ebINT y,ebBOOL isExtending); */
#define DM_SETCURSORPOS				(WM_USER + 37)
#define HANDLE_DM_SETCURSORPOS(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(int)(short)ebLOWORD(lParam),(int)(unsigned short)ebHIWORD(lParam),(ebBOOL)(wParam))
#define FORWARD_DM_SETCURSORPOS(hWnd,x,y,isExtending,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_SETCURSORPOS,(ebWPARAM)(isExtending),ebMAKELPARAM((x),(y)))
#define ebDebugger_SetCursorPos(hWnd,x,y,isExtending) FORWARD_DM_SETCURSORPOS(hWnd,x,y,isExtending,MESSAGEROUTINE)

/* ebBOOL ebDebugger_GetDirty(ebHWND hWnd); */
#define DM_GETDIRTY					(WM_USER + 1)
#define HANDLE_DM_GETDIRTY(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)(hWnd)
#define FORWARD_DM_GETDIRTY(hWnd,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_GETDIRTY,0,0L)
#define ebDebugger_GetDirty(hWnd) FORWARD_DM_GETDIRTY(hWnd,MESSAGEROUTINE)

/* void ebDebugger_Trace(ebHWND hWnd); */
#define DM_TRACE					(WM_USER + 2)
#define HANDLE_DM_TRACE(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_TRACE(hWnd,fn) (void)(fn)((hWnd),DM_TRACE,0,0L)
#define ebDebugger_Trace(hWnd) FORWARD_DM_TRACE(hWnd,MESSAGEROUTINE)

/* void ebDebugger_Step(ebHWND hWnd); */
#define DM_STEP						(WM_USER + 3)
#define HANDLE_DM_STEP(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_STEP(hWnd,fn) (void)(fn)((hWnd),DM_STEP,0,0L)
#define ebDebugger_Step(hWnd) FORWARD_DM_STEP(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_ToggleBreakpoint(ebHWND hWnd,ebWORD wLineNo); */
#define DM_TOGGLEBREAKPOINT			(WM_USER + 4)
#define HANDLE_DM_TOGGLEBREAKPOINT(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(ebUINT)wParam)
#define FORWARD_DM_TOGGLEBREAKPOINT(hWnd,wLineNo,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_TOGGLEBREAKPOINT,(ebWPARAM)wLineNo,0L)
#define ebDebugger_ToggleBreakpoint(hWnd,wLineNo) FORWARD_DM_TOGGLEBREAKPOINT(hWnd,wLineNo,MESSAGEROUTINE)

/* void ebDebugger_EditCut(ebHWND hWnd); */
#define DM_EDITCUT	 			(WM_USER + 53)
#define HANDLE_DM_EDITCUT(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_EDITCUT(hWnd,fn) (void)(fn)((hWnd),DM_EDITCUT,0,0L)
#define ebDebugger_EditCut(hWnd) FORWARD_DM_EDITCUT(hWnd,MESSAGEROUTINE)

/* void ebDebugger_EditCopy(ebHWND hWnd); */
#define DM_EDITCOPY					(WM_USER + 54)
#define HANDLE_DM_EDITCOPY(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_EDITCOPY(hWnd,fn) (void)(fn)((hWnd),DM_EDITCOPY,0,0L)
#define ebDebugger_EditCopy(hWnd) FORWARD_DM_EDITCOPY(hWnd,MESSAGEROUTINE)

/* void ebDebugger_EditPaste(ebHWND hWnd); */
#define DM_EDITPASTE					(WM_USER + 55)
#define HANDLE_DM_EDITPASTE(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_EDITPASTE(hWnd,fn) (void)(fn)((hWnd),DM_EDITPASTE,0,0L)
#define ebDebugger_EditPaste(hWnd) FORWARD_DM_EDITPASTE(hWnd,MESSAGEROUTINE)

/* void ebDebugger_EditUndo(ebHWND hWnd); */
#define DM_EDITUNDO					(WM_USER + 56)
#define HANDLE_DM_EDITUNDO(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_EDITUNDO(hWnd,fn) (void)(fn)((hWnd),DM_EDITUNDO,0,0L)
#define ebDebugger_EditUndo(hWnd) FORWARD_DM_EDITUNDO(hWnd,MESSAGEROUTINE)

/* void ebDebugger_EditClear(ebHWND hWnd); */
#define DM_EDITCLEAR					(WM_USER + 57)
#define HANDLE_DM_EDITCLEAR(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_EDITCLEAR(hWnd,fn) (void)(fn)((hWnd),DM_EDITCLEAR,0,0L)
#define ebDebugger_EditClear(hWnd) FORWARD_DM_EDITCLEAR(hWnd,MESSAGEROUTINE)

/* void ebDebugger_SetHelpMode(ebHWND hWnd,ebBOOL isHelp,ebHCURSOR hCursor); */
#define DM_SETHELPMODE				(WM_USER + 58)
#define HANDLE_DM_SETHELPMODE(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd,(ebBOOL)wParam,(ebHCURSOR)(sizeof(ebHCURSOR) == 2 ? ebLOWORD(lParam) : (ebDWORD)lParam)),0L)
#define FORWARD_DM_SETHELPMODE(hWnd,isHelp,hCursor,fn) (void)(fn)((hWnd),DM_SETHELPMODE,(ebWPARAM)(isHelp),sizeof(ebHCURSOR) == 2 ? ebMAKELPARAM(hCursor,0) : (LPARAM)hCursor)
#define ebDebugger_SetHelpMode(hWnd,isHelp,hCursor) FORWARD_DM_SETHELPMODE(hWnd,isHelp,hCursor,MESSAGEROUTINE)

/* ebBOOL ebDebugger_SetText(ebHWND hWnd,ebLPCTSTR lpText); */
#define DM_SETTEXT				(WM_USER + 59)
#define HANDLE_DM_SETTEXT(hWnd,wParam,lParam,fn) (LRESULT)(fn)(hWnd,(ebLPCTSTR)lParam)
#define FORWARD_DM_SETTEXT(hWnd,lpText,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_SETTEXT,0,(ebLPARAM)(ebLPCTSTR)(lpText))
#define ebDebugger_SetText(hWnd,lpText) FORWARD_DM_SETTEXT(hWnd,lpText,MESSAGEROUTINE)

/* ebUINT ebDebugger_GetText(ebHWND hWnd,_ebUINT wMaxLen,ebLPTSTR lpText); */
#define DM_GETTEXT				(WM_USER + 60)
#define HANDLE_DM_GETTEXT(hWnd,wParam,lParam,fn) (LRESULT)(fn)(hWnd,(ebUINT)wParam,(ebLPTSTR)lParam)
#define FORWARD_DM_GETTEXT(hWnd,uMaxLen,lpText,fn) (ebUINT)(fn)((hWnd),DM_GETTEXT,(ebWPARAM)(ebUINT)(uMaxLen),(ebLPARAM)(ebLPTSTR)(lpText))
#define ebDebugger_GetText(hWnd,uMaxLen,lpText) FORWARD_DM_GETTEXT(hWnd,uMaxLen,lpText,MESSAGEROUTINE)

/* ebUINT ebDebugger_GetTextLength(ebHWND hWnd); */
#define DM_GETTEXTLENGTH			(WM_USER + 61)
#define HANDLE_DM_GETTEXTLENGTH(hWnd,wParam,lParam,fn) (LRESULT)(fn)(hWnd)
#define FORWARD_DM_GETTEXTLENGTH(hWnd,fn) (ebUINT)(fn)((hWnd),DM_GETTEXTLENGTH,0,0)
#define ebDebugger_GetTextLength(hWnd) FORWARD_DM_GETTEXTLENGTH(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_SetTitle(ebHWND hWnd,ebLPCTSTR lpTitle); */
#define DM_SETTITLE			(WM_USER + 62)
#define HANDLE_DM_SETTITLE(hWnd,wParam,lParam,fn) (LRESULT)(fn)(hWnd,(ebLPTSTR)lParam)
#define FORWARD_DM_SETTITLE(hWnd,lpTitle,fn) (ebWORD)(ebDWORD)(fn)((hWnd),DM_SETTITLE,0,(ebLPARAM)(ebLPTSTR)(lpTitle))
#define ebDebugger_SetTitle(hWnd,lpTitle) FORWARD_DM_SETTITLE(hWnd,lpTitle,MESSAGEROUTINE)

typedef struct tagEBTEXTCOLORS {
	ebDWORD dwSize;					/* size of this structure */
	ebCOLOR CommentBackground;		/* background color for comments */
	ebCOLOR CommentForeground;		/* foreground color for comments */
	ebCOLOR NormalBackground;		/* background color for normal text */
	ebCOLOR NormalForeground;		/* foreground color for normal text */
	ebCOLOR BreakBackground;		/* background color for breakpoints */
	ebCOLOR BreakForeground;		/* foreground color for breakpoints */
	ebCOLOR SelectBackground;		/* background color for text selection */
	ebCOLOR SelectForeground;		/* foreground color for text selection */
	ebCOLOR CurLineBackground;		/* background color for the current line of execution */
	ebCOLOR CurLineForeground;		/* foreground color for the current line of execution */
	ebCOLOR KeywordForeground;		/* foreground color for reserved words */
	ebCOLOR KeywordBackground;		/* background color for reserved words */
	ebCOLOR IdentifierForeground;	/* foreground color for identifiers */
	ebCOLOR IdentifierBackground;	/* background color for identifiers */
	ebCOLOR DisabledForeground;	/* foreground color for disabled normal text */
} ebTEXTCOLORS,ebFAR *ebLPTEXTCOLORS;

/* void ebDebugger_SetTextColors(ebHWND hWnd,ebLPTEXTCOLORS lpColors); */
#define DM_SETTEXTCOLORS			(WM_USER + 63)
#define HANDLE_DM_SETTEXTCOLORS(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd,(ebLPTEXTCOLORS)lParam),0L)
#define FORWARD_DM_SETTEXTCOLORS(hWnd,lpColors,fn) (void)(fn)((hWnd),DM_SETTEXTCOLORS,0,(ebLPARAM)(ebLPTEXTCOLORS)(lpColors))
#define ebDebugger_SetTextColors(hWnd,lpColors) FORWARD_DM_SETTEXTCOLORS(hWnd,lpColors,MESSAGEROUTINE)

/* void ebDebugger_GetTextColors(ebHWND hWnd,ebLPTEXTCOLORS lpColors); */
#define DM_GETTEXTCOLORS			(WM_USER + 64)
#define HANDLE_DM_GETTEXTCOLORS(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd,(ebLPTEXTCOLORS)lParam),0L)
#define FORWARD_DM_GETTEXTCOLORS(hWnd,lpColors,fn) (void)(fn)((hWnd),DM_GETTEXTCOLORS,0,(ebLPARAM)(ebLPTEXTCOLORS)(lpColors))
#define ebDebugger_GetTextColors(hWnd,lpColors) FORWARD_DM_GETTEXTCOLORS(hWnd,lpColors,MESSAGEROUTINE)

/* ebBOOL ebDebugger_EnableTextColors(ebHWND hWnd,ebBOOL isEnabled); */
#define DM_ENABLETEXTCOLORS			(WM_USER + 65)
#define HANDLE_DM_ENABLETEXTCOLORS(hWnd,wParam,lParam,fn) (LRESULT)(fn)(hWnd,(ebBOOL)wParam)
#define FORWARD_DM_ENABLETEXTCOLORS(hWnd,isEnabled,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_ENABLETEXTCOLORS,(ebWPARAM)(ebBOOL)(isEnabled),0L)
#define ebDebugger_EnableTextColors(hWnd,isEnabled) FORWARD_DM_ENABLETEXTCOLORS(hWnd,isEnabled,MESSAGEROUTINE)

/* ebBOOL ebDebugger_SetFont(ebHWND hWnd,ebHFONT hFont); */
#define DM_SETFONT			(WM_USER + 66)
#define HANDLE_DM_SETFONT(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)((fn)(hWnd,(ebHFONT)wParam),0L)
#define FORWARD_DM_SETFONT(hWnd,hFont,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_SETFONT,(ebWPARAM)(ebHFONT)(hFont),0L)
#define ebDebugger_SetFont(hWnd,hFont) FORWARD_DM_SETFONT(hWnd,hFont,MESSAGEROUTINE)

/* ebHFONT ebDebugger_GetFont(ebHWND hWnd); */
#define DM_GETFONT			(WM_USER + 67)
#define HANDLE_DM_GETFONT(hWnd,wParam,lParam,fn) (LRESULT)(ebLPVOID)(ebHFONT)(fn)(hWnd)
#define FORWARD_DM_GETFONT(hWnd,fn) (ebHFONT)(fn)((hWnd),DM_GETFONT,0,0L)
#define ebDebugger_GetFont(hWnd) FORWARD_DM_GETFONT(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_EnableCompilerError(ebHWND hWnd,ebBOOL isEnabled); */
#define DM_ENABLECOMPILERERROR		(WM_USER + 68)
#define HANDLE_DM_ENABLECOMPILERERROR(hWnd,wParam,lParam,fn) (LRESULT)(ebBOOL)(fn)(hWnd,(ebBOOL)wParam)
#define FORWARD_DM_ENABLECOMPILERERROR(hWnd,isEnabled,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_ENABLECOMPILERERROR,(ebWPARAM)(isEnabled),0L)
#define ebDebugger_EnableCompilerError(hWnd,isEnabled) FORWARD_DM_ENABLECOMPILERERROR(hWnd,isEnabled,MESSAGEROUTINE)

/* void ebDebugger_SetTabStop(ebHWND hWnd,ebWORD wNumChars); */
#define DM_SETTABSTOP			(WM_USER + 70)
#define HANDLE_DM_SETTABSTOP(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(_ebWORD)(wParam)),0L)
#define FORWARD_DM_SETTABSTOP(hWnd,wNumChars,fn) (void)(fn)((hWnd),DM_SETTABSTOP,(ebWPARAM)(_ebWORD)(wNumChars),0)
#define ebDebugger_SetTabStop(hWnd,wNumChars) FORWARD_DM_SETTABSTOP(hWnd,wNumChars,MESSAGEROUTINE)

/* ebWORD ebDebugger_GetTabStop(ebHWND hWnd); */
#define DM_GETTABSTOP			(WM_USER + 71)
#define HANDLE_DM_GETTABSTOP(hWnd,wParam,lParam,fn) (LRESULT)(ebWORD)(ebBOOL)(fn)(hWnd)
#define FORWARD_DM_GETTABSTOP(hWnd,fn) (ebBOOL)(ebWORD)(fn)((hWnd),DM_GETTABSTOP,0,0L)
#define ebDebugger_GetTabStop(hWnd) FORWARD_DM_GETTABSTOP(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_IsReadOnly(ebHWND hWnd); */
#define DM_ISREADONLY			(WM_USER + 72)
#define HANDLE_DM_ISREADONLY(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)(hWnd)
#define FORWARD_DM_ISREADONLY(hWnd,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_ISREADONLY,0,0L)
#define ebDebugger_IsReadOnly(hWnd) FORWARD_DM_ISREADONLY(hWnd,MESSAGEROUTINE)

/* void ebDebugger_SetReadOnly(ebHWND hWnd,ebBOOL isReadOnly); */
#define DM_SETREADONLY			(WM_USER + 73)
#define HANDLE_DM_SETREADONLY(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(ebBOOL)(wParam)),0L)
#define FORWARD_DM_SETREADONLY(hWnd,isReadOnly,fn) (void)(fn)((hWnd),DM_SETREADONLY,(ebWPARAM)(ebBOOL)(isReadOnly),0)
#define ebDebugger_SetReadOnly(hWnd,isReadOnly) FORWARD_DM_SETREADONLY(hWnd,isReadOnly,MESSAGEROUTINE)

/* ebDWORD ebDebugger_GetCursorPos(ebHWND hWnd); */
#define DM_GETCURSORPOS		(WM_USER + 74)
#define HANDLE_DM_GETCURSORPOS(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(fn)(hWnd)
#define FORWARD_DM_GETCURSORPOS(hWnd,fn) (ebDWORD)(fn)((hWnd),DM_GETCURSORPOS,0,0L)
#define ebDebugger_GetCursorPos(hWnd) FORWARD_DM_GETCURSORPOS(hWnd,MESSAGEROUTINE)

/* ebINT ebDebugger_QueryBreakpoints(ebHWND hWnd,ebLPWORD lpLines); */
#define DM_QUERYBREAKPOINTS	(WM_USER + 75)
#define HANDLE_DM_QUERYBREAKPOINTS(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(int)(fn)((hWnd),(ebLPWORD)lParam)
#define FORWARD_DM_QUERYBREAKPOINTS(hWnd,lpLines,fn) (int)(ebDWORD)(fn)((hWnd),DM_QUERYBREAKPOINTS,0,(ebLPARAM)(ebLPWORD)(lpLines))
#define ebDebugger_QueryBreakpoints(hWnd,lpLines) FORWARD_DM_QUERYBREAKPOINTS(hWnd,lpLines,MESSAGEROUTINE)

/* ebBOOL ebDebugger_SetScript(ebHWND hWnd,ebHSCRIPT hScript); */
#define DM_SETSCRIPT		(WM_USER + 76)
#define HANDLE_DM_SETSCRIPT(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(fn)((hWnd),(ebHSCRIPT)lParam)
#define FORWARD_DM_SETSCRIPT(hWnd,hScript,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_SETSCRIPT,0,(ebLPARAM)(ebHSCRIPT)(hScript))
#define ebDebugger_SetScript(hWnd,hScript) FORWARD_DM_SETSCRIPT(hWnd,hScript,MESSAGEROUTINE)

/* ebBOOL ebDebugger_SetThread(ebHWND hWnd,ebHTHREAD hThread); */
#define DM_SETTHREAD		(WM_USER + 77)
#define HANDLE_DM_SETTHREAD(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(fn)((hWnd),(ebHTHREAD)lParam)
#define FORWARD_DM_SETTHREAD(hWnd,hThread,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_SETTHREAD,0,(ebLPARAM)(ebHTHREAD)(hThread))
#define ebDebugger_SetThread(hWnd,hThread) FORWARD_DM_SETTHREAD(hWnd,hThread,MESSAGEROUTINE)

/* void ebDebugger_SetNotificationProc(ebHWND hWnd,ebNOTIFICATIONPROC lpfnNotifyProc) */
#define DM_SETNOTIFICATIONPROC		(WM_USER + 78)
#define HANDLE_DM_SETNOTIFICATIONPROC(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(ebNOTIFICATIONPROC)lParam),0)
#define FORWARD_DM_SETNOTIFICATIONPROC(hWnd,lpfnNotifyProc,fn) (void)(ebDWORD)(fn)((hWnd),DM_SETNOTIFICATIONPROC,0,(ebLPARAM)(ebNOTIFICATIONPROC)(lpfnNotifyProc))
#define ebDebugger_SetNotificationProc(hWnd,lpfnNotifyProc) FORWARD_DM_SETNOTIFICATIONPROC(hWnd,lpfnNotifyProc,MESSAGEROUTINE)

/* void ebDebugger_SetNotificationData(ebHWND hWnd,long lData) */
#define DM_SETNOTIFICATIONDATA		(WM_USER + 79)
#define HANDLE_DM_SETNOTIFICATIONDATA(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(long)lParam),0L)
#define FORWARD_DM_SETNOTIFICATIONDATA(hWnd,lData,fn) (void)(fn)((hWnd),DM_SETNOTIFICATIONDATA,0,(ebLPARAM)(long)(lData))
#define ebDebugger_SetNotificationData(hWnd,lData) FORWARD_DM_SETNOTIFICATIONDATA(hWnd,lData,MESSAGEROUTINE)

/* ebINT ebDebugger_GetActivePane(ebHWND hWnd) */
#define DM_GETACTIVEPANE		(WM_USER + 80)
#define HANDLE_DM_GETACTIVEPANE(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(fn)(hWnd)
#define FORWARD_DM_GETACTIVEPANE(hWnd,fn) (int)(ebDWORD)(fn)((hWnd),DM_GETACTIVEPANE,0,0L)
#define ebDebugger_GetActivePane(hWnd) FORWARD_DM_GETACTIVEPANE(hWnd,MESSAGEROUTINE)

/* long ebDebugger_GetLong(ebHWND hWnd,ebINT iWhich); */
#define DM_GETLONG	 			(WM_USER + 81)
#define HANDLE_DM_GETLONG(hWnd,wParam,lParam,fn) (LRESULT)(long)(fn)((hWnd),(int)(wParam))
#define FORWARD_DM_GETLONG(hWnd,iWhich,fn) (long)(fn)((hWnd),DM_GETLONG,(ebWPARAM)(iWhich),0L)
#define ebDebugger_GetLong(hWnd,iWhich) FORWARD_DM_GETLONG(hWnd,iWhich,MESSAGEROUTINE)

/* void ebDebugger_SetLong(ebHWND hWnd,ebINT iWhich,long lValue); */
#define DM_SETLONG	 			(WM_USER + 82)
#define HANDLE_DM_SETLONG(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(int)(wParam),(long)(lParam)),0)
#define FORWARD_DM_SETLONG(hWnd,iWhich,lValue,fn) (void)(fn)((hWnd),DM_SETLONG,(ebWPARAM)(iWhich),(ebLPARAM)(long)(lValue))
#define ebDebugger_SetLong(hWnd,iWhich,lValue) FORWARD_DM_SETLONG(hWnd,iWhich,lValue,MESSAGEROUTINE)

/* ebWORD ebDebugger_GetNumLines(ebHWND hWnd); */
#define DM_GETNUMLINES			(WM_USER + 83)
#define HANDLE_DM_GETNUMLINES(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebWORD)(fn)(hWnd)
#define FORWARD_DM_GETNUMLINES(hWnd,fn) (ebWORD)(ebDWORD)(fn)((hWnd),DM_GETNUMLINES,0,0L)
#define ebDebugger_GetNumLines(hWnd) FORWARD_DM_GETNUMLINES(hWnd,MESSAGEROUTINE)

/* ebINT ebDebugger_SetUndoLevels(ebHWND hWnd,ebINT iLevels); */
#define DM_SETUNDOLEVELS		(WM_USER + 84)
#define HANDLE_DM_SETUNDOLEVELS(hWnd,wParam,lParam,fn) (LRESULT)(int)(fn)((hWnd),(int)wParam)
#define FORWARD_DM_SETUNDOLEVELS(hWnd,iLevels,fn) (int)(ebDWORD)(fn)((hWnd),DM_SETUNDOLEVELS,(ebWPARAM)(int)(iLevels),0L)
#define ebDebugger_SetUndoLevels(hWnd,iLevels) FORWARD_DM_SETUNDOLEVELS(hWnd,iLevels,MESSAGEROUTINE)

/* void ebDebugger_UpdateWatchPane(ebHWND hWnd,ebINT nCmd); */
#define DM_UPDATEWATCHPANE		(WM_USER + 85)
#define HANDLE_DM_UPDATEWATCHPANE(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(int)wParam),0L)
#define FORWARD_DM_UPDATEWATCHPANE(hWnd,iCmd,fn) (int)(ebDWORD)(fn)((hWnd),DM_UPDATEWATCHPANE,(ebWPARAM)(int)(iCmd),0L)
#define ebDebugger_UpdateWatchPane(hWnd,iCmd) FORWARD_DM_UPDATEWATCHPANE(hWnd,iCmd,MESSAGEROUTINE)

/* void ebDebugger_SetScriptName(ebHWND hWnd,ebLPCTSTR lpName); */
#define DM_SETSCRIPTNAME		(WM_USER + 86)
#define HANDLE_DM_SETSCRIPTNAME(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(ebLPCTSTR)lParam),0L)
#define FORWARD_DM_SETSCRIPTNAME(hWnd,lpName,fn) (int)(ebDWORD)(fn)((hWnd),DM_SETSCRIPTNAME,0,(ebLPARAM)(ebLPCTSTR)(lpName))
#define ebDebugger_SetScriptName(hWnd,lpName) FORWARD_DM_SETSCRIPTNAME(hWnd,lpName,MESSAGEROUTINE)

/* ebINT ebDebugger_GetCurWatch(ebHWND hWnd); */
#define DM_GETCURWATCH			(WM_USER + 87)
#define HANDLE_DM_GETCURWATCH(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(int)(fn)(hWnd)
#define FORWARD_DM_GETCURWATCH(hWnd,fn) (int)(ebDWORD)(fn)((hWnd),DM_GETCURWATCH,0,0L)
#define ebDebugger_GetCurWatch(hWnd) FORWARD_DM_GETCURWATCH(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_EnableUpdate(ebHWND hWnd,ebBOOL isUpdate); */
#define DM_ENABLEUPDATE				(WM_USER + 88)
#define HANDLE_DM_ENABLEUPDATE(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(ebBOOL)(wParam))
#define FORWARD_DM_ENABLEUPDATE(hWnd,isUpdate,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_ENABLEUPDATE,(ebWPARAM)(isUpdate),0L)
#define ebDebugger_EnableUpdate(hWnd,isUpdate) FORWARD_DM_ENABLEUPDATE(hWnd,isUpdate,MESSAGEROUTINE)

/* ebWORD ebDebugger_GetLine(ebHWND hWnd,ebWORD wLineNo,ebBOOL isExpandTabs,ebLPTSTR lpText); */
#define DM_GETLINE				(WM_USER + 89)
#define HANDLE_DM_GETLINE(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd,(ebWORD)wParam,(ebLPTSTR)lParam))
#define FORWARD_DM_GETLINE(hWnd,wLineNo,isExpandTabs,lpText,fn) \
	(ebWORD)(ebDWORD)(fn)((hWnd),DM_GETLINE,(ebWPARAM)(ebWORD)(wLineNo),(ebLPARAM)(ebLPTSTR)((*(lpText) = (isExpandTabs) ? (TCHAR)'\t':(TCHAR)'\0'),(lpText)))
#define ebDebugger_GetLine(hWnd,wLineNo,isExpandTabs,lpText) FORWARD_DM_GETLINE(hWnd,wLineNo,isExpandTabs,lpText,MESSAGEROUTINE)
	
/* ebWORD ebDebugger_GetLineLength(ebHWND hWnd,ebWORD wLineNo,ebBOOL isExpandTabs); */
#define DM_GETLINELENGTH			(WM_USER + 90)
#define HANDLE_DM_GETLINELENGTH(hWnd,wParam,lParam,fn) (LRESULT)(ebWORD)((fn)((hWnd),(ebWORD)wParam,(ebBOOL)lParam))
#define FORWARD_DM_GETLINELENGTH(hWnd,wLineNo,isExpandTabs,fn) (ebWORD)(ebDWORD)(fn)((hWnd),DM_GETLINELENGTH,(ebWPARAM)(wLineNo),(ebLPARAM)(ebBOOL)(isExpandTabs))
#define ebDebugger_GetLineLength(hWnd,wLineNo,isExpandTabs) FORWARD_DM_GETLINELENGTH(hWnd,wLineNo,isExpandTabs,MESSAGEROUTINE)

/* ebBOOL ebDebugger_SetFontEx(ebHWND hWnd,ebHFONT hFont,ebINT iWhichFont); */
#define DM_SETFONTEX			(WM_USER + 91)
#define HANDLE_DM_SETFONTEX(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)((fn)((hWnd),(ebHFONT)wParam,(int)lParam))
#define FORWARD_DM_SETFONTEX(hWnd,hFont,iWhichFont,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_SETFONTEX,(ebWPARAM)(ebHFONT)(hFont),(ebLPARAM)(int)(iWhichFont))
#define ebDebugger_SetFontEx(hWnd,hFont,iWhichFont) FORWARD_DM_SETFONTEX(hWnd,hFont,iWhichFont,MESSAGEROUTINE)

/* ebHFONT ebDebugger_GetFontEx(ebHWND hWnd,ebINT iWhichFont); */
#define DM_GETFONTEX			(WM_USER + 92)
#define HANDLE_DM_GETFONTEX(hWnd,wParam,lParam,fn) (LRESULT)(UINT)(ebHFONT)(fn)((hWnd),(int)(wParam))
#define FORWARD_DM_GETFONTEX(hWnd,iWhichFont,fn) (ebHFONT)(fn)((hWnd),DM_GETFONTEX,(ebWPARAM)(int)(iWhichFont),0L)
#define ebDebugger_GetFontEx(hWnd,iWhichFont) FORWARD_DM_GETFONT(hWnd,iWhichFont,MESSAGEROUTINE)

/* void ebDebugger_SelectLines(ebHWND hWnd,ebWORD wFirst,ebWORD wLast,ebBOOL isScrollIntoView); */
#define DM_SELECTLINES			(WM_USER + 93)
#define HANDLE_DM_SELECTLINES(hWnd,wParam,lParam,fn) ((fn)((hWnd),ebLOWORD(lParam),ebHIWORD(lParam),(ebBOOL)wParam),0)
#define FORWARD_DM_SELECTLINES(hWnd,wFirst,wLast,isScrollIntoView,fn) (fn)((hWnd),DM_SELECTLINES,(ebWPARAM)(isScrollIntoView),ebMAKELPARAM(wFirst,wLast))
#define ebDebugger_SelectLines(hWnd,wFirst,wLast,isScrollIntoView) FORWARD_DM_SELECTLINES(hWnd,wFirst,wLast,isScrollIntoView,MESSAGEROUTINE)

/* ebHWND ebDebugger_GetDialogEditorWindow(ebHWND hWnd); */
#define DM_GETDIALOGEDITORWINDOW		(WM_USER + 94)
#define HANDLE_DM_GETDIALOGEDITORWINDOW(hWnd,wParam,lParam,fn) (LRESULT)(UINT)(ebHWND)(fn)(hWnd)
#define FORWARD_DM_GETDIALOGEDITORWINDOW(hWnd,fn) (ebHWND)(fn)((hWnd),DM_GETDIALOGEDITORWINDOW,0,0L)
#define ebDebugger_GetDialogEditorWindow(hWnd) FORWARD_DM_GETDIALOGEDITORWINDOW(hWnd,MESSAGEROUTINE)

/* ebBOOL ebDebugger_SetAutoIndent(ebHWND hWndDebugger,ebBOOL isAutoIndent); */
#define DM_SETAUTOINDENT		(WM_USER + 95)
#define HANDLE_DM_SETAUTOINDENT(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(fn)((hWnd),(ebBOOL)wParam)
#define FORWARD_DM_SETAUTOINDENT(hWnd,isAutoIndent,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_SETAUTOINDENT,(ebWPARAM)(isAutoIndent),0)
#define ebDebugger_SetAutoIndent(hWnd,isAutoIndent) FORWARD_DM_SETAUTOINDENT(hWnd,isAutoIndent,MESSAGEROUTINE)

/* ebBOOL ebDebugger_SetAutoCase(ebHWND hWndDebugger,ebBOOL isAutoCase); */
#define DM_SETAUTOCASE		(WM_USER + 96)
#define HANDLE_DM_SETAUTOCASE(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(fn)((hWnd),(ebBOOL)wParam)
#define FORWARD_DM_SETAUTOCASE(hWnd,isAutoCase,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_SETAUTOCASE,(ebWPARAM)(isAutoCase),0)
#define ebDebugger_SetAutoCase(hWnd,isAutoCase) FORWARD_DM_SETAUTOCASE(hWnd,isAutoCase,MESSAGEROUTINE)

/* void ebDebugger_AutoCaseText(ebHWND hWnd); */
#define DM_AUTOCASETEXT			(WM_USER + 97)
#define HANDLE_DM_AUTOCASETEXT(hWnd,wParam,lParam,fn) (LRESULT)((fn)(hWnd),0L)
#define FORWARD_DM_AUTOCASETEXT(hWnd,fn) (void)(fn)((hWnd),DM_AUTOCASETEXT,0,0L)
#define ebDebugger_AutoCaseText(hWnd) FORWARD_DM_AUTOCASETEXT(hWnd,MESSAGEROUTINE)

/* void ebDebugger_SetResource(ebHWND hWnd,ebLPVOID lpResource); */
#define DM_SETRESOURCE		(WM_USER + 98)
#define HANDLE_DM_SETRESOURCE(hWnd,wParam,lParam,fn) (LRESULT)((fn)((hWnd),(ebLPVOID)lParam),0L)
#define FORWARD_DM_SETRESOURCE(hWnd,lpResource,fn) (int)(ebDWORD)(fn)((hWnd),DM_SETRESOURCE,0,(ebLPARAM)(ebLPVOID)(lpResource))
#define ebDebugger_SetResource(hWnd,lpResource) FORWARD_DM_SETRESOURCE(hWnd,lpResource,MESSAGEROUTINE)

/* WM_USER+98 reserved for future use */

/* ebBOOL ebDebugger_SetStatusText(ebHWND hWnd,ebLPCTSTR lpText); */
#define DM_SETSTATUSTEXT		(WM_USER + 99)
#define HANDLE_DM_SETSTATUSTEXT(hWnd,wParam,lParam,fn) (LRESULT)(ebDWORD)(ebBOOL)(fn)((hWnd),(ebLPTSTR)lParam)
#define FORWARD_DM_SETSTATUSTEXT(hWnd,lpText,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_SETSTATUSTEXT,0,(ebLPARAM)(ebLPTSTR)(lpText))
#define ebDebugger_SetStatusText(hWnd,lpText) FORWARD_DM_SETSTATUSTEXT(hWnd,lpText,MESSAGEROUTINE)

/* ebBOOL ebDebugger_TypeText(ebHWND hWnd,ebLPCTSTR lpText); */
#define DM_TYPETEXT				(WM_USER + 100)
#define HANDLE_DM_TYPETEXT(hWnd,wParam,lParam,fn) (LRESULT)(fn)(hWnd,(ebLPCTSTR)lParam)
#define FORWARD_DM_TYPETEXT(hWnd,lpText,fn) (ebBOOL)(ebDWORD)(fn)((hWnd),DM_TYPETEXT,0,(ebLPARAM)(ebLPCTSTR)(lpText))
#define ebDebugger_TypeText(hWnd,lpText) FORWARD_DM_TYPETEXT(hWnd,lpText,MESSAGEROUTINE)

#define DM_FIRST		(WM_USER + 1)
#define DM_LAST		DM_TYPETEXT

/* Debugger control identifiers */
#define ebID_EDITPANE				1		/* edit pane */
#define ebID_STATUSBAR				2		/* status bar */
#define ebID_PANESEPARATOR			3		/* pane separator */
#define ebID_WATCHPANE				4		/* watch pane */
#define ebID_TOOLBAR             5    	/* toolbar */
#define ebID_WATCHPANEHEADER		7		/* watch pane header */

/* (D)ebugger (N)otifications */
#define DN_EXECUTESTART				0x0100		/* set execution state ON */
#define DN_EXECUTEEND				0x0101		/* set execution state OFF */
#define DN_GO							0x0102		/* execution beginning */
#define DN_STOP						0x0103		/* execution stopping */
#define DN_CLOSE						0x0104		/* debugger control wants to close */
#define DN_CHANGED					0x0105		/* code or script has been changed */
#define DN_COMPILE					0x0106		/* code is about to be compiled */
#define DN_SWITCH						0x0107		/* switching to another script */
#define DN_DIALOGSTART				0x0108		/* a dialog is being invoked */
#define DN_DIALOGEND					0x0109		/* a dialog is going away */
#define DN_MESSAGEBOX				0x010A		/* message box is about to display */
#define DN_CURSORMOVE				0x010B		/* cursor changed position */
#define DN_TOGGLEBREAKPOINT		0x010C		/* breakpoint about to be toggled */
#define DN_HELP						0x010D		/* help requested */
#define DN_DIALOGEDITBEGIN			0x010E		/* dialog editing has begun */
#define DN_DIALOGEDITEND			0x010F		/* dialog editing has ended */
#define DN_COMPILEEND				0x0110		/* compiling is done */
#define DN_REQUESTHELP				0x0111		/* help requested for error */
#define DN_ERRSPACE					0x0112		/* out of memory */
#define DN_TEXTLIMIT					0x0113		/* reached text limit */
#define DN_LINELIMIT					0x0114		/* reached maximum line length */
#define DN_TOOLTIP					0x0115		/* tooltip to be displayed or hidden */
#define DN_COMMAND					0x0116		/* command from the debugger */
#define DN_UNSWITCH					0x0117		/* sent when switching back to default script */
#define DN_RIGHTBUTTONDOWN			0x0118		/* sent to host when the right mouse button is pressed */
#define DN_RIGHTBUTTONUP 			0x0119		/* sent to host when the right mouse button is released */
#define DN_RIGHTBUTTON				DN_RIGHTBUTTONDOWN	/* backward compatibility */
#define DN_DLGINFO_INIT				0x011A		/* dialog structure initialized */
#define DN_DLGINFO_TERM				0x011B		/* dialog structure uninitialized */

/* Debugger Error Message Ids (used with DN_MESSAGEBOX notification) */
#define ebDBG_ERR_MEMORY   			1 			/* Out of memory Msg */
#define ebDBG_ERR_TEXTLIMIT			2 			/* Text limit Reached Msg */
#define ebDBG_ERR_LINELIMIT			3 			/* Line limit reached Msg */
#define ebDBG_ERR_LINETRUNCATE		4 			/* Line length limit reached - Truncating Msg */
#define ebDBG_ERR_BASIC				0x10000		/* Basic Error */

#ifdef WANT_PACK
#pragma pack()
#endif /* WANT_PACK */

#endif /* !RC_INVOKED */

/* Debugger help identifiers */
#define ebDBGHELP_FILE								1 		/* File menu */
#define ebDBGHELP_EDIT								2 		/* Edit menu */
#define ebDBGHELP_RUN								3 		/* Run menu */
#define ebDBGHELP_DEBUG								4 		/* Debug menu */
#define ebDBGHELP_HELP								5 		/* Help menu */
#define ebDBGHELP_SYSTEM							6 		/* System menu */
#define ebDBGHELP_FILE_EXIT						7		/* "Exit and Return" command on the File menu */
#define ebDBGHELP_EDIT_UNDO						8		/* "Undo" command on the Edit menu */
#define ebDBGHELP_EDIT_CUT							9		/* "Cut" command on the Edit menu */
#define ebDBGHELP_EDIT_COPY						10		/* "Copy" command on the Edit menu */
#define ebDBGHELP_EDIT_PASTE						11		/* "Paste" command on the Edit menu */
#define ebDBGHELP_EDIT_CLEAR						12		/* "Delete" command on the Edit menu */
#define ebDBGHELP_EDIT_FIND						13		/* "Find..." command on the Edit menu */
#define ebDBGHELP_EDIT_FINDNEXT					14		/* "Find Next" command on the Edit menu */
#define ebDBGHELP_EDIT_REPLACE					15		/* "Replace..." command on the Edit menu */
#define ebDBGHELP_EDIT_GOTOLINE					16		/* "Goto Line..." command on the Edit menu */
#define ebDBGHELP_EDIT_INSERTDIALOG				17		/* "Insert New Dialog..." command on the Edit menu */
#define ebDBGHELP_EDIT_EDITDIALOG				18		/* "Edit Dialog..." command on the Edit menu */
#define ebDBGHELP_RUN_START						19		/* "Start" command on the Run menu */
#define ebDBGHELP_RUN_END							20		/* "End" command on the Run menu */
#define ebDBGHELP_RUN_SYNTAXCHECK				21		/* "Syntax Check" command on the Run menu */
#define ebDBGHELP_DEBUG_ADDWATCH					22		/* "Add Watch..." command on the Debug menu */
#define ebDBGHELP_DEBUG_DELETEWATCH				23		/* "Delete Watch" command on the Debug menu */
#define ebDBGHELP_DEBUG_MODIFY					24		/* "Modify" command on the Debug menu */
#define ebDBGHELP_DEBUG_SINGLESTEP				25		/* "Single Step" command on the Debug menu */
#define ebDBGHELP_DEBUG_PROCEDURESTEP			26		/* "Procedure Step" command on the Debug menu */
#define ebDBGHELP_DEBUG_TOGGLEBREAKPOINT		27		/* "Toggle Breakpoint" command on the Debug menu */
#define ebDBGHELP_DEBUG_CLEARBREAKPOINTS		28		/* "Clear All Breakpoints" command on the Debug menu */
#define ebDBGHELP_DEBUG_SETNEXTSTATEMENT		29		/* "Set Next Statement" command on the Debug menu */
#define ebDBGHELP_DEBUG_CALLS						30		/* "Calls" command */
#define ebDBGHELP_HELP_CONTENTS					31		/* "Contents" command on the Help menu */
#define ebDBGHELP_HELP_SEARCH						32		/* "Search for Help on..." command on the Help menu */
#define ebDBGHELP_SYSTEM_RESTORE					33		/* "Restore" command on the system menu */
#define ebDBGHELP_SYSTEM_MOVE						34		/* "Move" command on the system menu */
#define ebDBGHELP_SYSTEM_SIZE						35		/* "Size" command on the system menu */
#define ebDBGHELP_SYSTEM_MINIMIZE				36		/* "Minimize" command on the system menu */
#define ebDBGHELP_SYSTEM_MAXIMIZE				37		/* "Maximize" command on the system menu */
#define ebDBGHELP_SYSTEM_CLOSE					38		/* "Close" command on the system menu */
#define ebDBGHELP_SYSTEM_SWITCHTO				39		/* "Switch To..." command on the system menu */
#define ebDBGHELP_DIALOG_ADDWATCH				40		/* Add Watch dialog */
#define ebDBGHELP_DIALOG_MODIFY					41		/* Modify dialog box */
#define ebDBGHELP_DIALOG_GOTOLINE				42		/* Goto Line dialog box */
#define ebDBGHELP_DIALOG_CALLS					43		/* Calls dialog box */
#define ebDBGHELP_DIALOGEDITOR					44		/* Help from the Dialog Editor */
#define ebDBGHELP_WATCHWINDOW						45		/* Watch window */
#define ebDBGHELP_KEYWORD							46		/* keyword help */
#define ebDBGHELP_EDITWINDOW						47		/* Edit window */
#define ebDBGHELP_DIALOGABOUT						48		/* Dialog About was selected */
#define ebDBGHELP_CONTENTS							49		/* "Contents" command was selected from the Help menu */
#define ebDBGHELP_SEARCH							50		/* "Search for Help on" command was selected from the Help menu */
#define ebDBGHELP_PANESEPARATOR					51		/* Pane separator window */
#define ebDBGHELP_STATUSBAR						52		/* Status bar window */
#define ebDBGHELP_DIALOG_FIND						53		/* Find dialog box */
#define ebDBGHELP_DIALOG_REPLACE					54		/* Replace dialog box */
#define ebDBGHELP_ERROR								55		/* Error dialog box */
#define ebDBGHELP_EDIT_SELECTALL					56		/* "Select All" command on the Edit menu */
#define ebDBGHELP_RUN_BREAK						57		/* "Break" command */

#endif	/* EBWIN && EBWIN32 && EBOS2 && EBMAC EBIRIX */

/* --------------------------------------------------------------------------
 * Debugger Dialog APIs
 * ----------------------------------------------------------------------- */
#if defined(EBWIN) || defined(EBWIN32)

#ifndef RC_INVOKED

#ifdef WANT_PACK
#pragma pack(1)
#endif /* WANT_PACK */

/* Other debugger stuff... */
#define DEBUGFINDTEXTSZ	 				128					/* size of find text */

typedef struct tagebDEBUGGER {
	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 * Member					  		       Returned?		Description
	 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	ebDWORD lStructSize;						/* No				size of the structure for version determination */
	ebHINSTANCE hInstance;					/* No				holds the instance of BasicScript returned from ebInit */
	ebLPCSTR lpScriptIn;	  					/* No				holds the initial script */
	ebLPSTR lpScriptOut;	 	 				/* Yes (rc==1)	holds the new script, if one was saved */
	ebHCODE hCodeIn;	 						/* No				initial compiled code structure */
	ebHCODE hCodeOut;							/* Yes (rc==1)	final compiled code structure, if one was saved */
	ebLPSTR lpTitle;			 				/* No				far pointer to window title, or NULL for default title */
	ebINT watchwindowheight; 				/* Yes  			height of the listbox, if it is open, otherwise 0 */
	ebINT x,y,width,height;					/* Yes  			positions of the window, or 0x8000/0x80000000 if the default window position is desired */
	ebBOOL isMatchCase;						/* Yes  			TRUE if matching case, FALSE otherwise */
	char findtext[DEBUGFINDTEXTSZ];		/* Yes  			text to find */
	char reptext[DEBUGFINDTEXTSZ]; 	 	/* Yes  			text to replace with */
	ebHWND hWndParent;	 					/* No				handle to parent window */
	ebHFONT hFont;								/* No				handle to font to use (NULL to use default font) */
	ebENTRYINFO ei;							/* No				describes the entry point, parameters, and return buffer */
	ebLPSTR lpWatchesIn;						/* No				initial watch variables */
	ebLPSTR lpWatchesOut;					/* Yes  			pointer to watch variables */
	long lParam;								/* No				long value to attach to the thread at position 0 */
	ebNOTIFICATIONPROC lpfnNotify;		/* No				pointer to the notification procedure */
	long NotifyData;							/* No				long value to pass through to the notification procedure */
	ebLPCTSTR lpName;							/* No				name of the script (appears in watch pane, call stack) */
	ebLPVOID hResource;						/* No				replacement resource DLL */
} ebDEBUGGER,ebFAR *ebLPDEBUGGER;

/* (D)ebugger (r)eturn (c)odes */
#define DRC_OUTOFMEMORY			-1			/* insufficient memory to invoke macro editor */
#define DRC_CANTCREATEWINDOW	-2			/* insufficnent system resource to create window */
#define DRC_CANTFINDLIBRARY	-3			/* unable to locate debugger control library */
#define DRC_SAVED					1			/* user wants to save the macro */
#define DRC_CANCEL				2			/* user cancelled editing */

ebINT ebAPI ebDebugger(ebLPDEBUGGER debug);

#ifdef WANT_PACK
#pragma pack()
#endif /* WANT_PACK */

#endif	/* EBWIN || EBWIN32 */

#endif /* !RC_INVOKED */

/* --------------------------------------------------------------------------
 * Dialog Editor APIs
 * ----------------------------------------------------------------------- */
#if defined(EBWIN) || defined(EBWIN32)	/* Dialog Editor only on these platforms */
#ifndef RC_INVOKED

#define DLGEDITOR_APPMODE			0		/* invoke as application */
#define DLGEDITOR_EMBEDDEDMODE	1		/* invoke as dialog */

#define ebDLGMSG_SAVE				0		/* request to save a dialog template */
#define ebDLGMSG_ABOUTBOX			1		/* request to invoke the About Box */
#define ebDLGMSG_HELP				2		/* request for Help */
#define ebDLGMSG_SHOW				3		/* showing the Dialog Editor */
#define ebDLGMSG_EXIT				4		/* exiting the Dialog Editor */
#define ebDLGMSG_GETRESOURCEDLL	5		/* asking for a resource DLL */
#define ebDLGMSG_INFOBOX			6		/* showing an info box */

#endif /* !RC_INVOKED */

/*
 * ebDLGHELP_* Values and Context Usage
 *
 * ebDLGHELP_RSVD* are reserved for future additional values
 * DB is short for dialog box
 * MB is short for message box
 * SF1 is short for Shift-F1
 */
#define ebDLGHELP_NONE 									0		/* No help for topic or help does not apply	*/
#define ebDLGHELP_CONTENTS								1		/* Help|Contents */
#define ebDLGHELP_SEARCH  								2		/* Help|Search */
#define ebDLGHELP_DIALOGBOXINFOBOX					3		/* Help for Dialog Box Information DB	*/
#define ebDLGHELP_OKBUTTONINFOBOX 					4		/* Help for Default OK Button Information DB	*/
#define ebDLGHELP_CANCELBUTTONINFOBOX				5		/* Help for Default Cancel Button Information DB	*/
#define ebDLGHELP_HELPBUTTONINFOBOX					6		/* Help for Default Cancel Button Information DB	*/
#define ebDLGHELP_PUSHBUTTONINFOBOX	 				7		/* Help for Push Button Information DB	*/
#define ebDLGHELP_OPTIONBUTTONINFOBOX				8		/* Help for Option Button Information DB	*/
#define ebDLGHELP_CHECKBOXINFOBOX	 				9		/* Help for Check Box Information DB	*/
#define ebDLGHELP_GROUPBOXINFOBOX	 				10		/* Help for Group Box Information DB	*/
#define ebDLGHELP_TEXTINFOBOX			 				11		/* Help for Text Information DB	*/
#define ebDLGHELP_TEXTBOXINFOBOX	 					12		/* Help for Text Box Information DB	*/
#define ebDLGHELP_LISTBOXINFOBOX	 					13		/* Help for List Box Information DB	*/
#define ebDLGHELP_COMBOBOXINFOBOX	 				14		/* Help for Combo Box Information DB	*/
#define ebDLGHELP_DROPLISTBOXINFOBOX 				15		/* Help for Drop List Box Informatin DB	*/
#define ebDLGHELP_PICTUREINFOBOX	 					16		/* Help for Picture Information DB	*/
#define ebDLGHELP_PICTBTNINFOBOX						17		/* Help for Picture Button Information DB	*/
#define ebDLGHELP_RSVD1				 					18
#define ebDLGHELP_RSVD2				 					19
#define ebDLGHELP_RSVD3				 					20
#define ebDLGHELP_COMMDLGGETPICTLIBFILE			21		/* Help for Select a Picture Library DB	*/
#define ebDLGHELP_COMMDLGGETPICTFILE   			22		/* Help for Select a Picture File DB	*/
#define ebDLGHELP_COMMDLGGETDLGFILE	   			23		/* Help for Open Dialog File DB	*/
#define ebDLGHELP_COMMDLGSAVEDLGFILE   			24		/* Help for Save Dialog File DB	*/
#define ebDLGHELP_COMMDLGGETHELPFILE				25		/* Help for Select Help File */
#define ebDLGHELP_RSVD6				   				26
#define ebDLGHELP_GRIDINFOBOX		   				27		/* Help for Grid DB	*/
#define ebDLGHELP_TRANSLATIONERRORBOX  			28		/* Help for Dialog Translation Errors DB	*/
#define ebDLGHELP_WIN32CAPTUREBOX	   			29		/* Help for Capture Dialog Box */
#define ebDLGHELP_RSVD11				   			30
#define ebDLGHELP_RSVD12				   			31
#define ebDLGHELP_RSVD13				   			32
#define ebDLGHELP_RSVD14				   			33
#define ebDLGHELP_MBGENERIC			   			34		/* Reserved value	*/
#define ebDLGHELP_MBINVALNR			   			35		/* F1 Help for invalid number or number out of range MB	*/
#define ebDLGHELP_MBGRIDUNITSRANGE	   			36		/* F1 Help for grid unit setting out of range MB	*/
#define ebDLGHELP_MBNOTPOSITIVENR	   			37		/* F1 Help for width and height number must be positive MB	*/
#define ebDLGHELP_MBOUTSIDEDIALOG	   			38		/* F1 Help for dialog specified outside visible area MB	*/
#define ebDLGHELP_MBINVALSTRVAR		   			39		/* F1 Help for invalid string variable MB	*/
#define ebDLGHELP_MBINVALVARNAME		   			40		/* F1 Help for invalid variable name MB	*/
#define ebDLGHELP_MBINVALFUNCNAME	   			41		/* F1 Help for invalid dialog function name MB	*/
#define ebDLGHELP_MBINVALIDENT		   			42		/* F1 Help for invalid control identifier name MB	*/
#define ebDLGHELP_MBACCELKEYINUSE	   			43		/* F1 Help for accelerator key already assigned	MB */
#define ebDLGHELP_MBIDENTINUSE		   			44		/* F1 Help for control identifier already assigned MB	*/
#define ebDLGHELP_MBNOPUSHBTNINDLG	   			45		/* F1 Help for no push button in dialog MB	*/
#define ebDLGHELP_MBNOPUSHBTNINSIDE	   			46		/* F1 Help for no push button inside visible dialog window MB	*/
#define ebDLGHELP_MBCTRLSOUTSIDEDIALOG 			47		/* F1 Help for control(s) outside dialog MB	*/
#define ebDLGHELP_MBIDENTMULTUSE	   				48		/* F1 Help for multiple use of identifier MB	*/
#define ebDLGHELP_MBACCELKEYMULTUSE	   			49		/* F1 Help for multiple use of accel key MB	*/
#define ebDLGHELP_MBDLGDATANOTINCLIPBRD			50		/* F1 Help for dialog data not in clipboard MB	*/
#define ebDLGHELP_MBNOTDIALOGBASICCODE 			51		/* F1 Help for not Basic dialog code MB	*/
#define ebDLGHELP_MBINVALFILENAME	   			52		/* F1 Help for invalid filename MB	*/
#define ebDLGHELP_MBFILENOTFOUND	   				53		/* F1 Help for file not found MB	*/
#define ebDLGHELP_MBNOTPICTFILE		   			54		/* F1 Help for not a picture file MB	*/
#define ebDLGHELP_MBPICTLIBNOTGIVEN	   			55		/* F1 Help for picture file not declared for the dialog MB	*/
#define ebDLGHELP_MBPICTNOTINLIB	   				56		/* F1 Help for picture is not in library	*/
#define ebDLGHELP_MBUNKNOWNERROR	   				57		/* Reserved */ 
#define ebDLGHELP_MBNODIALOGSTMTSINTEXT			58		/* F1 Help for test does not contain any dialog template statements MB	*/
#define ebDLGHELP_MBCANTDUPMAXCTRLS	   			59		/* F1 Help for Can't duplicate control because maximum controls already in dialog MB	*/
#define ebDLGHELP_MBCANTCREATEHAVEMAXCTRLS		60		/* F1 Help for Can't create control because maximum number of controls already in dialog MB	*/
#define ebDLGHELP_MBNUMBERREQUIRED 					61		/* F1 Help for Number required */
#define ebDLGHELP_MBNODIALOGSTOCAPTURE			 	62		/* F1 Help for No dialogs boxes to capture */
#define ebDLGHELP_RSVD19					   		63
#define ebDLGHELP_RSVD20					   		64
#define ebDLGHELP_RSVD21					   		65
#define ebDLGHELP_RSVD22					   		66
#define ebDLGHELP_RSVD23					   		67
#define ebDLGHELP_RSVD24					   		68
#define ebDLGHELP_RSVD25					   		69
#define ebDLGHELP_RSVD26					   		70
#define ebDLGHELP_RSVD27					   		71
#define ebDLGHELP_RSVD28					   		72
#define ebDLGHELP_RSVD29					   		73
#define ebDLGHELP_ASKSAVETOFILE		   			74		/* F1 Help for "Would you like to save the the dialog to file?" MB	*/
#define ebDLGHELP_ASKSAVETOCURRENTFILE 			75		/* F1 Help for "Would you like to save the dialog to current file?" MB	*/
#define ebDLGHELP_ASKINFILEOPENFORGETFILESAVE	76		/* F1 Help for "Error occurred during file save." MB	*/
#define ebDLGHELP_ASKSAVECHANGES	   				77		/* F1 Help for save to file or insert dialog template MB	*/
#define ebDLGHELP_ASKSAVECHANGESBEFOREPASTE		78		/* F1 Help for save changes before paste MB	*/
#define ebDLGHELP_ASKSAVECHANGESBEFORECAPTURE	79		/* F1 Help for save changes before capture MB	*/
#define ebDLGHELP_ASKEXITWITHOUTSAVING 			80		/* F1 Help for Exit without saving the dialog MB	*/
#define ebDLGHELP_ASKSAVETHENEXIT	   			81		/* F1 Help for Save the dialog to file then exit? MB	*/
#define ebDLGHELP_ASKSAVECHANGEONEXITANDRETURN	82		/* F1 Help for Do you want to save the dialog template? MB	*/
#define ebDLGHELP_ASKDELETEALLCTRLS	   		  	83		/* F1 Help for Do you want to delete all controls MB	*/
#define ebDLGHELP_ASKCREATEXOFYCTRLS   		  	84		/* F1 Help for Can't create X controls because max controls will be exceeded MB	*/
#define ebDLGHELP_RSVD30								85
#define ebDLGHELP_RSVD31								86
#define ebDLGHELP_RSVD32								87
#define ebDLGHELP_RSVD33								88
#define ebDLGHELP_RSVD34								89
#define ebDLGHELP_RSVD35								90
#define ebDLGHELP_RSVD36								91
#define ebDLGHELP_RSVD37								92
#define ebDLGHELP_RSVD38								93
#define ebDLGHELP_RSVD39								94
#define ebDLGHELP_RSVD40								95
#define ebDLGHELP_RSVD41								96
#define ebDLGHELP_RSVD42								97
#define ebDLGHELP_CMDStatusBar						98		/* SF1 Help for Status bar	*/
#define ebDLGHELP_CMDSelector							99		/* SF1 Help for BtnSelector	*/
#define ebDLGHELP_CMDSYSSize							100	/* SF1 Help for System Size menu item	*/
#define ebDLGHELP_CMDSYSMove							101	/* SF1 Help for System Move menu item	*/
#define ebDLGHELP_CMDSYSMinimize						102	/* SF1 Help for System Minimize menu item	*/
#define ebDLGHELP_CMDSYSMaximize						103	/* SF1 Help for System Maximize menu item	*/
#define ebDLGHELP_CMDSYSClose							104	/* SF1 Help for System Close menu item	*/
#define ebDLGHELP_CMDSYSRestore						105	/* SF1 Help for System Restore menu item	*/
#define ebDLGHELP_CMDSYSTasklist						106	/* SF1 Help for System Tasklist menu item	*/
#define ebDLGHELP_RSVD44								107
#define ebDLGHELP_RSVD45								108
#define ebDLGHELP_RSVD46								109
#define ebDLGHELP_CMDFILENew							110	/* SF1 Help for File|New	*/
#define ebDLGHELP_CMDFILEOpen							111	/* SF1 Help for File|Open	*/
#define ebDLGHELP_CMDFILESave							112	/* SF1 Help for File|Save	*/
#define ebDLGHELP_CMDFILESaveAs						113	/* SF1 Help for File|SaveAs	*/
#define ebDLGHELP_CMDFILETestDialog					114	/* SF1 Help for File|TestDialog	*/
#define ebDLGHELP_CMDFILECaptureDialog				115	/* SF1 Help for File|CapturDialog	*/
#define ebDLGHELP_CMDFILEExit							116	/* SF1 Help for File|Exit	*/
#define ebDLGHELP_CMDFILEUpdate						117	/* SF1 Help for File|Update	*/
#define ebDLGHELP_CMDFILEExitAndReturn				118	/* SF1 Help for File|ExitAndReturn	*/
#define ebDLGHELP_CMDEDITUndo							119	/* SF1 Help for Edit|Undo	*/
#define ebDLGHELP_CMDEDITCut							120	/* SF1 Help for Edit|Cut	*/
#define ebDLGHELP_CMDEDITCopy							121	/* SF1 Help for Edit|Copy	*/
#define ebDLGHELP_CMDEDITPaste						122	/* SF1 Help for Edit|Paste	*/
#define ebDLGHELP_CMDEDITDelete						123	/* SF1 Help for Edit|Delete	*/
#define ebDLGHELP_CMDEDITDuplicate					124	/* SF1 Help for Edit|Duplicate	*/
#define ebDLGHELP_CMDEDITSizeToText					125	/* SF1 Help for Edit|SizeToText	*/
#define ebDLGHELP_CMDEDITInfo							126	/* SF1 Help for Edit|Info	*/
#define ebDLGHELP_CMDEDITGrid							127	/* SF1 Help for Edit|Grid	*/
#define ebDLGHELP_CMDOKBtn								128	/* SF1 Help for Controls|OKBtn or BtnOK	*/
#define ebDLGHELP_CMDCancelBtn						129	/* SF1 Help for Controls|CancelBtn or BtnCancel	*/
#define ebDLGHELP_CMDHelpBtn							130	/* SF1 Help for Controls|HelpBtn or BtnCancel	*/
#define ebDLGHELP_CMDPushBtn							131	/* SF1 Help for Controls|PushBtn or BtnPush	*/
#define ebDLGHELP_CMDRadioBtn							132	/* SF1 Help for Controls|RadioBtn or BtnRadio	*/
#define ebDLGHELP_CMDCheckBox							133	/* SF1 Help for Controls|CheckBox or BtnCheck	*/
#define ebDLGHELP_CMDGroupBox							134	/* SF1 Help for Controls|GroupBox ror BtnGroup	*/
#define ebDLGHELP_CMDText								135	/* SF1 Help for Controls|Text or BtnText	*/
#define ebDLGHELP_CMDTextBox							136	/* SF1 Help for Controls|TextBox or BtnTextBox	*/
#define ebDLGHELP_CMDListBox							137	/* SF1 Help for Controls|ListBox or BtnListBox	*/
#define ebDLGHELP_CMDComboBox							138	/* SF1 Help for Controls|ComboBox or BtnComboBox	*/
#define ebDLGHELP_CMDDropListBox						139	/* SF1 Help for Controls|DropListBox or BtnDropListBox	*/
#define ebDLGHELP_CMDPicture							140	/* SF1 Help for Controls|Picture or BtnPicture	*/
#define ebDLGHELP_CMDPictureButton					141	/* SF1 Help for Controls|Picture button or BtnPictureButton	*/
#define ebDLGHELP_RSVD48								142
#define ebDLGHELP_RSVD49								143
#define ebDLGHELP_CMDClient							144	/* SF1 Help for Client (Window that contains the Dialog control) */
#define ebDLGHELP_CMDDialog							145 	/* SF1 Help for Dialog control	*/
#define ebDLGHELP_CMDHELPAbout						146	/* SF1 Help for Help|About	*/
#define ebDLGHELP_CMDFILE								147	/* File menuitems */
#define ebDLGHELP_CMDEDIT								148	/* Edit menuitems */
#define ebDLGHELP_CONTROLTOOLS						149	/* Control tools btns */
#define ebDLGHELP_CMDHELP								150	/* Help menuitems */
#define ebDLGHELP_ASKSAVECHANGEONEXITANDRETURNNOCANCEL	151		/* F1 Help for Do you want to save the dialog template? MB	*/
/* End of Dialog Editor help constants */

#ifndef RC_INVOKED

typedef ebBOOL (ebCALLBACK _ebDLGPROCA)(long lPassThrough, ebUINT umsg, ebDWORD dwParam1, ebDWORD dwParam2);
typedef _ebDLGPROCA *ebDLGPROCA;

typedef ebBOOL (ebCALLBACK _ebDLGPROCW)(long lPassThrough, ebUINT umsg, ebDWORD dwParam1, ebDWORD dwParam2);
typedef _ebDLGPROCW *ebDLGPROCW;

#ifdef EBWIDE
typedef ebDLGPROCW ebDLGPROC;
#else
typedef ebDLGPROCA ebDLGPROC;
#endif	/* EBWIDE */

#ifdef WANT_PACK
#pragma pack(1)
#endif /* WANT_PACK */

typedef struct tagebDLGINFOA {
	ebUINT uMode;					/* DLGEDITOR_APPMODE or DLGEDITOR_EMBEDDEDMODE */
	ebHWND hwndParent;			/* parent window */
	ebBOOL bUse3D;					/* TRUE if using 3D controls */
	ebINT x;							/* initial screen position */
	ebINT y;							/* CW_USEDEFAULT if default values */
	ebINT cx;						/* initial size */
	ebINT cy;						/* CW_USEDEFAULT if default values */
	ebBOOL bMinimized;			/* TRUE if last window state of the Dialog Editor was minimized */
	ebBOOL bMaximized;			/* TRUE if last window state of the Dialog Editor was maximized */
	ebINT XGridUnits;				/* initial X grid settings (must not be zero) */
	ebINT YGridUnits;				/* initial Y grid settings (must not be zero) */
	ebBOOL bShowGrid;				/* TRUE if grid is shown */
	ebBOOL bCanMinimize;			/* TRUE if Dialog Editor has a minimize box */
	ebBOOL bCanMaximize;			/* TRUE if Dialog Editor has a maximize box */
	ebLPSTR pszTitle;				/* caption of the Dialog Editor main window */
	ebLPSTR pszBasicTextIn;		/* initial dialog template */
	ebDLGPROCA pfnDlgProc;		/* pointer to dialog callback procedure */
	long lPassThrough;			/* application-defined data passed to dialog callback procedure */
	ebLPSTR lpPrefix;				/* pointer to the prefix for each line when the template is output */
	ebBOOL bShowCaptureMenu;	/* TRUE if showing the capture menu */
	ebLPSTR pszResDllName;		/* name of alternative resoruce file */
	ebLPSTR pszFileName;			/* name of a file, if initial template should be from a file */
	ebLPVOID lpReserved;			/* reserved and should be NULL */
} ebDLGINFOA,ebFAR *ebLPDLGINFOA;

typedef struct tagDLGINFOW {
	ebUINT uMode; 					/* DLGEDITOR_APPMODE or DLGEDITOR_EMBEDDEDMODE */
	ebHWND hwndParent;			/* parent window */
	ebBOOL bUse3D;					/* TRUE if using 3D controls */
	ebINT x;							/* initial screen position */
	ebINT y;							/* CW_USEDEFAULT if default values */
	ebINT cx;  						/* initial size */
	ebINT cy;  						/* CW_USEDEFAULT if default values */
	ebBOOL bMinimized;			/* TRUE if last window state of the Dialog Editor was minimized */
	ebBOOL bMaximized;			/* TRUE if last window state of the Dialog Editor was maximized */
	ebINT XGridUnits;				/* initial X grid settings (must not be zero) */
	ebINT YGridUnits;				/* initial Y grid settings (must not be zero) */
	ebBOOL bShowGrid;				/* TRUE if grid is shown */
	ebBOOL bCanMinimize;			/* TRUE if Dialog Editor has a minimize box */
	ebBOOL bCanMaximize;			/* TRUE if Dialog Editor has a maximize box */
	ebLPWSTR pszTitle;			/* caption of the Dialog Editor main window */
	ebLPWSTR pszBasicTextIn;	/* initial dialog template */
	ebDLGPROCA pfnDlgProc;		/* pointer to dialog callback procedure */
	long lPassThrough;			/* application-defined data passed to dialog callback procedure */
	ebLPWSTR lpPrefix;			/* pointer to the prefix for each line when the template is output */
	ebBOOL bShowCaptureMenu;	/* TRUE if showing the capture menu */
	ebLPWSTR pszResDllName;		/* name of alternative resoruce file */
	ebLPWSTR pszFileName;		/* name of a file, if initial template should be from a file */
	ebLPVOID lpReserved;			/* reserved and should be NULL */
} ebDLGINFOW,ebFAR *ebLPDLGINFOW;

#ifdef WANT_PACK
#pragma pack()
#endif /* WANT_PACK */

#ifdef EBWIDE
typedef ebDLGINFOW ebDLGINFO;
typedef ebLPDLGINFOW ebLPDLGINFO;
#else
typedef ebDLGINFOA ebDLGINFO;
typedef ebLPDLGINFOA ebLPDLGINFO;
#endif	/* EBWIDE */

ebINT ebAPI ebStartDlgEditorA(ebLPDLGINFOA lpdi);
ebINT ebAPI ebStartDlgEditorW(ebLPDLGINFOW lpdi);

#ifdef EBWIDE
#define ebStartDlgEditor ebStartDlgEditorW
#else
#define ebStartDlgEditor ebStartDlgEditorA
#endif	/* EBWIDE */

typedef ebBOOL (ebAPI _ebSTARTDLGEDITORPROCA)(ebLPDLGINFOA lpdi);
typedef _ebSTARTDLGEDITORPROCA *ebSTARTDLGEDITORPROCA;

typedef ebBOOL (ebAPI _ebSTARTDLGEDITORPROCW)(ebLPDLGINFOW lpdi);
typedef _ebSTARTDLGEDITORPROCW *ebSTARTDLGEDITORPROCW;

#ifdef EBWIDE
typedef ebSTARTDLGEDITORPROCW ebSTARTDLGEDITORPROC;
#else
typedef ebSTARTDLGEDITORPROCA ebSTARTDLGEDITORPROC;
#endif	/* EBWIDE */

ebDWORD ebAPI ebDlgEditorGetVersion(void);
typedef ebDWORD (ebAPI *ebDLGEDITORGETVERSIONPROC)(void);

#endif /* !RC_INVOKED */

#endif /* EBWIN || EBWIN32 */

/* --------------------------------------------------------------------------
 * OEM-Specific Information
 * ----------------------------------------------------------------------- */
#ifdef EBMAC
	#ifdef RC_INVOKED
		#include "eboem.h"
	#else	/* !RC_INVOKED */
		#ifdef _EBOEM_H_QUOTES_
			#include "eboem.h"
		#else	/* !_EBOEM_H_QUOTES_ */
			#include <eboem.h>
		#endif	/*!_EBOEM_H_QUOTES_ */
	#endif /* !RC_INVOKED */
#else	/* !EBMAC */
	#ifdef _EBOEM_H_QUOTES_
		#include "eboem.h"
	#else	/* !_EBOEM_H_QUOTES_ */
		#include <eboem.h>
	#endif	/*!_EBOEM_H_QUOTES_ */
#endif /* !EBMAC */

/* Module Names  */
#define PRODUCT_OLE_NAME	ebOEM ebPLATFORM ebTEXT("OL") ebVERSION	/* OLE 2.0 Object Support */
#define PRODUCT_COM_NAME	ebOEM ebPLATFORM ebTEXT("CM") ebVERSION	/* Compiler */
#define PRODUCT_RUN_NAME	ebOEM ebPLATFORM ebTEXT("RN") ebVERSION	/* Runtime */
#define PRODUCT_PUB_NAME	ebOEM ebPLATFORM ebTEXT("PB") ebVERSION	/* Public Extension Manager */
#define PRODUCT_REC_NAME	ebOEM ebPLATFORM ebTEXT("RC") ebVERSION	/* Recorder */
#define PRODUCT_DC_NAME		ebOEM ebPLATFORM ebTEXT("DC") ebVERSION	/* Debugger Control */
#define PRODUCT_DD_NAME		ebOEM ebPLATFORM ebTEXT("DD") ebVERSION	/* Debugger Dialog */
#define PRODUCT_DED_NAME	ebOEM ebPLATFORM ebTEXT("DG") ebVERSION	/* Dialog Editor DLL */
#define PRODUCT_DEE_NAME	ebOEM ebPLATFORM ebTEXT("DE") ebVERSION	/* Dialog Editor Executable */
#define PRODUCT_DCX_NAME	ebOEM ebPLATFORM ebTEXT("CX") ebVERSION	/* Summit Controls DLL */
#define PRODUCT_STB_NAME	ebOEM ebPLATFORM ebTEXT("ST") ebVERSION	/* EXE stub */
#define PRODUCT_DB_NAME		ebOEM ebPLATFORM ebTEXT("DB") ebVERSION	/* Database Extensions */
#define PRODUCT_TL_NAME		ebOEM ebPLATFORM ebTEXT("TL") ebVERSION	/* OLE 2.0 TypeLib support */

/* External file names  */
#define PRODUCT_INI_FILE		ebOEM ebVERSION ebTEXT(".INI")	/* INI file name (undefined if not used)  */
 
/* Class Names  */
#define PRODUCT_EDIT_CLASS		ebOEM ebPLATFORM ebVERSION ebTEXT("_Edit")		/* class name for programmer's edit control  */
#define PRODUCT_DEBUG_CLASS	ebOEM ebPLATFORM ebVERSION ebTEXT("_Debug")		/* class name for the debugger control  */
 
/* --------------------------------------------------------------------------
 * Stuff for Public Extensions
 * ----------------------------------------------------------------------- */
#define APPMODNAMESZ 80		/* length of identifier for public extension module names */

#ifdef EBNLM
#ifndef RC_INVOKED

/*
 * Structure used when creating public extension for NetWare
 */
typedef struct tagNLMINFOSTRUCT {
	ebBOOL isPermanent;							/* TRUE If this is a permanent extension */
	char szModuleName[APPMODNAMESZ];			/* module name */
	ebBOOL (*lpfnInit)(int);					/* extension initialization procedure */
	void (*lpfnTerm)(int);						/* extension termination procedure */
	ebCALLBACKPROC lpfnCall;					/* extension callback procedure */
	ebLPVOID (*lpfnGetPrototypes)(void);	/* routine called to get prototypes for this extension */
	void (*lpfnFreePrototypes)(ebLPVOID);	/* routine called to free prototypes for this extension */
} NLMINFOSTRUCT,ebFAR *LPNLMINFOSTRUCT;

#endif /* !RC_INVOKED */
#endif	/* EBNLM */

#ifdef EBMAC

#define EXT_INFO_RES	'XINF'/* info res name for public extensions */
#define EXT_INFO_ID 8899	/* info res ID for public extensions */

#ifdef REZ

type 'XINF' {
	integer;			/* isPermanent */
	pstring;			/* szModuleName */
	align word;
};

#endif	/* REZ */

#ifndef RC_INVOKED

/*
 * Header used to create public extensions for Macintosh
 */
#include <CodeFragments.h>

/*
 *	This defines a routine type that must handle events which BasicScript
 *	cannot handle as part of event processing dialogs.
 *	
 */
#include	<Events.h>
 
typedef void (*ebMACEVENTHANDLER)(EventRecord event);
typedef void (*ebMACEVENTHANDLER2)(long lParam, EventRecord* event);
typedef void (ebCALLBACK _ebDLGPROC)(ebHTHREAD hThread,ebHWND hDlg,ebINT nCode,long lParam);
typedef _ebDLGPROC *ebDLGPROC;

/*
 *	To register this handler with BasicScript, call ebSendMessage with the
 *	message ebIM_SETOSVALUE and an index of 0. For example,
 *
 *		ebSendMessage(myInstance,ebIM_SETOSVALUE,0,(ebLONG)myEventHandler);
 *		ebSendMessage(myInstance,ebIM_SETDLGPROC,0,(ebLONG)myDlgHandler);
 */

#ifdef __MWERKS__
/*   Switches back to the Metrowerks calling convention.  Functions return pointers
 *   in register A0.  68K Macintosh only.  
 */
#pragma pointers_in_A0
#endif	/* __MWERKS__ */

#ifndef NEWMACDBGR
#ifndef __DC__
#include "dc.h"
#endif /* __DC__ */
#endif

#endif /* !RC_INVOKED */
#endif	/* EBMAC */

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* _EB_H_ */



