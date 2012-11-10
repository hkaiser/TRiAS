// Wrapperfunktionen für BScriptRuntime ---------------------------------------
// File: DAOWRAP.CPP

#include "stdafx.h"

#include <eb.h>

extern HINSTANCE g_hBScript;		// BasicRuntime

// ebGetVariant ---------------------------------------------------------------
typedef void (ebAPI EB_GETVARIANTPROCEX)(ebARGS, int, ebLPVARIANT);
typedef EB_GETVARIANTPROCEX *ebGETVARIANTPROCEX;

void ebAPI ebGetVariantEx (ebARGS lpArgs, int index, ebVARIANT *lpVariant)
{
static ebGETVARIANTPROCEX F = NULL;

	if (NULL == F) F = (ebGETVARIANTPROCEX)GetProcAddress (g_hBScript, "ebGetVariantEx");
	F (lpArgs, index, lpVariant);
}

// ebSetVariant ---------------------------------------------------------------
typedef void (ebAPI EB_SETVARIANTPROC)(ebARGS, int, ebLPVARIANT);
typedef EB_SETVARIANTPROC *ebSETVARIANTPROC;

void ebAPI ebSetVariant(ebARGS lpArgs, int index, ebLPVARIANT lpVariant)
{
static ebSETVARIANTPROC F = NULL;

	if (NULL == F) F = (ebSETVARIANTPROC)GetProcAddress (g_hBScript, "ebSetVariant");
	F (lpArgs, index, lpVariant);
}

// ebFreeVariant --------------------------------------------------------------
typedef void (ebAPI EB_FREEVARIANTPROC)(ebHOBJECT, ebLPVARIANT);
typedef EB_FREEVARIANTPROC *ebFREEVARIANTPROC;

void ebAPI ebFreeVariant (ebHOBJECT hObject, ebLPVARIANT lpVariant)
{
static ebFREEVARIANTPROC F = NULL;

	if (NULL == F) F = (ebFREEVARIANTPROC)GetProcAddress (g_hBScript, "ebFreeVariant");
	F (hObject, lpVariant);
}

// ebCreateString -------------------------------------------------------------
typedef ebHSUB (ebAPI EB_CREATESTRINGPROC)(ebHOBJECT, ebLPCSTR);
typedef EB_CREATESTRINGPROC *ebCREATESTRINGPROC;

ebHSUB ebAPI ebCreateString (ebHOBJECT hObject, ebLPCSTR lpStr)
{
static ebCREATESTRINGPROC F = NULL;

	if (NULL == F) F = (ebCREATESTRINGPROC)GetProcAddress (g_hBScript, "ebCreateString");
	return F(hObject, lpStr);
}

// ebFreeString ---------------------------------------------------------------
typedef ebHSUB (ebAPI EB_FREESTRINGPROC)(ebHOBJECT, _ebHSUB);
typedef EB_FREESTRINGPROC *ebFREESTRINGPROC;

void ebAPI ebFreeString (ebHOBJECT hObject, _ebHSUB hStr)
{
static ebFREESTRINGPROC F = NULL;

	if (NULL == F) F = (ebFREESTRINGPROC)GetProcAddress (g_hBScript, "ebFreeString");
	F (hObject, hStr);
}

// ebGetString ----------------------------------------------------------------
typedef ebHSUB (ebAPI EB_GETSTRINGPROC)(ebARGS, int);
typedef EB_GETSTRINGPROC *ebGETSTRINGPROC;

ebHSUB ebAPI ebGetString (ebARGS lpArgs, int index)
{
static ebGETSTRINGPROC F = NULL;

	if (NULL == F) F = (ebGETSTRINGPROC)GetProcAddress (g_hBScript, "ebGetString");
	return F(lpArgs, index);
}

// ebSetString ----------------------------------------------------------------
typedef void (ebAPI EB_SETSTRINGPROC)(ebARGS, int, ebHSUB);
typedef EB_SETSTRINGPROC *ebSETSTRINGPROC;

void ebAPI ebSetString (ebARGS lpArgs, int index, ebHSUB hStr)
{
static ebSETSTRINGPROC F = NULL;

	if (NULL == F) F = (ebSETSTRINGPROC)GetProcAddress (g_hBScript, "ebSetString");
	F (lpArgs, index, hStr);
}

// ebGetObject ----------------------------------------------------------------
typedef ebDWORD (ebAPI EB_GETOBJECT)(ebARGS, int);
typedef EB_GETOBJECT *ebGETOBJECT;

ebDWORD ebAPI ebGetObject (ebARGS lpArgs, int index)
{
static ebGETOBJECT F = NULL;

	if (NULL == F) F = (ebGETOBJECT)GetProcAddress (g_hBScript, "ebGetObject");
	return F(lpArgs, index);
}

// ebLockString ---------------------------------------------------------------
typedef ebLPSTR (ebAPI EB_LOCKSTRING)(ebHOBJECT, _ebHSUB);
typedef EB_LOCKSTRING *ebLOCKSTRING;

ebLPSTR ebAPI ebLockString (ebHOBJECT hObject, _ebHSUB hStr)
{
static ebLOCKSTRING F = NULL;

	if (NULL == F) F = (ebLOCKSTRING)GetProcAddress (g_hBScript, "ebLockString");
	return F(hObject, hStr);
}

// ebUnlockString -------------------------------------------------------------
typedef void (ebAPI EB_UNLOCKSTRING)(ebHOBJECT, _ebHSUB);
typedef EB_UNLOCKSTRING *ebUNLOCKSTRING;

void ebAPI ebUnlockString (ebHOBJECT hObject, _ebHSUB hStr)
{
static ebUNLOCKSTRING F = NULL;

	if (NULL == F) F = (ebUNLOCKSTRING)GetProcAddress (g_hBScript, "ebUnlockString");
	F(hObject, hStr);
}

// ebSetObject ----------------------------------------------------------------
typedef void (ebAPI EB_SETOBJECT)(ebARGS, int, ebDWORD);
typedef EB_SETOBJECT *ebSETOBJECT;

void ebAPI ebSetObject (ebARGS lpArgs, int index, ebDWORD dwObject)
{
static ebSETOBJECT F = NULL; 

	if (NULL == F) F = (ebSETOBJECT)GetProcAddress (g_hBScript, "ebSetObject");
	F (lpArgs, index, dwObject);
}

// ebGetInt -------------------------------------------------------------------
typedef short (ebAPI EB_GETINT)(ebARGS, int);
typedef EB_GETINT *ebGETINT;

short ebAPI ebGetInt (ebARGS lpArgs, int index)
{
static ebGETINT F = NULL; 

	if (NULL == F) F = (ebGETINT)GetProcAddress (g_hBScript, "ebGetInt");
	return F(lpArgs, index);
}

// ebSetInt -------------------------------------------------------------------
typedef void (ebAPI EB_SETINT)(ebARGS, int, _short);
typedef EB_SETINT *ebSETINT;

void ebAPI ebSetInt (ebARGS lpArgs, int index, _short i)
{
static ebSETINT F = NULL; 

	if (NULL == F) F = (ebSETINT)GetProcAddress (g_hBScript, "ebSetInt");
	F (lpArgs, index, i);
}

// ebGetLong ------------------------------------------------------------------
typedef long (ebAPI EB_GETLONG)(ebARGS, int);
typedef EB_GETLONG *ebGETLONG;

long ebAPI ebGetLong (ebARGS lpArgs, int index)
{
static ebGETLONG F = NULL;

	if (NULL == F) F = (ebGETLONG)GetProcAddress (g_hBScript, "ebGetLong");
	return F(lpArgs, index);
}

// ebSetLong ------------------------------------------------------------------
typedef void (ebAPI EB_SETLONG)(ebARGS, int, long);
typedef EB_SETLONG *ebSETLONG;

void ebAPI ebSetLong (ebARGS lpArgs, int index, long i)
{
static ebSETLONG F = NULL;

	if (NULL == F) F = (ebSETLONG)GetProcAddress (g_hBScript, "ebSetLong");
	F (lpArgs, index, i);
}

// ebGetDouble ----------------------------------------------------------------
typedef double (ebAPI EB_GETDOUBLE)(ebARGS, int);
typedef EB_GETDOUBLE *ebGETDOUBLE;

double ebAPI ebGetDouble (ebARGS lpArgs, int index)
{
static ebGETDOUBLE F = NULL;

	if (NULL == F) F = (ebGETDOUBLE)GetProcAddress (g_hBScript, "ebGetDouble");
	return F(lpArgs, index);
}

// ebSetDouble ----------------------------------------------------------------
typedef void (ebAPI EB_SETDOUBLE)(ebARGS, int, double);
typedef EB_SETDOUBLE *ebSETDOUBLE;

void ebAPI ebSetDouble (ebARGS lpArgs, int index, double d)
{
static ebSETDOUBLE F = NULL;

	if (NULL == F) F = (ebSETDOUBLE)GetProcAddress (g_hBScript, "ebSetDouble");
	F (lpArgs, index, d);
}

// ebGetDispatch --------------------------------------------------------------
typedef ebLPDISPATCH (ebAPI EB_GETDISPATCH)(ebHTHREAD, ebDWORD);
typedef EB_GETDISPATCH *ebGETDISPATCH;

ebLPDISPATCH ebAPI ebGetDispatch (ebHTHREAD hThread, ebDWORD dwId)
{
static ebGETDISPATCH F = NULL;

	if (NULL == F) F = (ebGETDISPATCH)GetProcAddress (g_hBScript, "ebGetDispatch");
	return F(hThread, dwId);
}

// ebCreateOleId --------------------------------------------------------------
typedef ebDWORD (ebAPI EB_CREATEOLEID)(ebHTHREAD, ebLPDISPATCH);
typedef EB_CREATEOLEID *ebCREATEOLEID;

ebDWORD ebAPI ebCreateOleId (ebHTHREAD hThread, ebLPDISPATCH lpDispatch)
{
static ebCREATEOLEID F = NULL;

	if (NULL == F) F = (ebCREATEOLEID)GetProcAddress (g_hBScript, "ebCreateOleId");
	return F(hThread, lpDispatch);
}

// ebRuntimeError -------------------------------------------------------------
typedef void (ebAPI EB_RUNTIMEERROR)(ebHTHREAD, ebBOOL, _ebWORD, ebLPCSTR);
typedef EB_RUNTIMEERROR *ebRUNTIMEERROR;

void ebAPI ebRuntimeError (ebHTHREAD hThread, ebBOOL isFatal, _ebWORD wErrNum, ebLPCSTR lpErrorText)
{
static ebRUNTIMEERROR F = NULL;

	if (NULL == F) F = (ebRUNTIMEERROR)GetProcAddress (g_hBScript, "ebRuntimeError");
	F(hThread, isFatal, wErrNum, lpErrorText);
}

// ebLockArrayData ------------------------------------------------------------
typedef ebLPVOID (ebAPI EB_LOCKARRAYDATA)(ebHOBJECT, const ebLPARRAY);
typedef EB_LOCKARRAYDATA *ebLOCKARRAYDATA;

ebLPVOID ebAPI ebLockArrayData (ebHOBJECT hObject, const ebLPARRAY lpHdr)
{
static ebLOCKARRAYDATA F = NULL;

	if (NULL == F) F = (ebLOCKARRAYDATA)GetProcAddress (g_hBScript, "ebLockArrayData");
	return F(hObject, lpHdr);
}

// ebUnlockArrayData ----------------------------------------------------------
typedef void (ebAPI EB_UNLOCKARRAYDATA)(ebHOBJECT, const ebLPARRAY);
typedef EB_UNLOCKARRAYDATA *ebUNLOCKARRAYDATA;

void ebAPI ebUnlockArrayData (ebHOBJECT hObject, const ebLPARRAY lpHdr)
{
static ebUNLOCKARRAYDATA F = NULL;

	if (NULL == F) F = (ebUNLOCKARRAYDATA)GetProcAddress (g_hBScript, "ebUnlockArrayData");
	F(hObject, lpHdr);
}

// ebRedimArray ---------------------------------------------------------------
typedef int (ebAPI EB_REDIMARRAY)(ebHOBJECT, _ebHSUB, _ebWORD);
typedef EB_REDIMARRAY *ebREDIMARRAY;

int ebAPI ebRedimArray (ebHOBJECT hObject, _ebHSUB hArray, _ebWORD wNumElements)
{
static ebREDIMARRAY F = NULL;

	if (NULL == F) F = (ebREDIMARRAY)GetProcAddress (g_hBScript, "ebRedimArray");
	return F(hObject, hArray, wNumElements);
}

// ebGetArray -----------------------------------------------------------------
typedef ebHSUB (ebAPI EB_GETARRAY)(ebARGS, int);
typedef EB_GETARRAY *ebGETARRAY;

ebHSUB ebAPI ebGetArray (ebARGS lpArgs, int index)
{
static ebGETARRAY F = NULL;

	if (NULL == F) F = (ebGETARRAY)GetProcAddress (g_hBScript, "ebGetArray");
	return F(lpArgs, index);
}

// ebLockBlk ------------------------------------------------------------------
typedef ebLPVOID (ebAPI EB_LOCKBLK)(ebHOBJECT, _ebHSUB);
typedef EB_LOCKBLK *ebLOCKBLK;

ebLPVOID ebAPI ebLockBlk (ebHOBJECT hObject, _ebHSUB hBlk)
{
static ebLOCKBLK F = NULL;

	if (NULL == F) F = (ebLOCKBLK)GetProcAddress (g_hBScript, "ebLockBlk");
	return F(hObject, hBlk);
}

// ebUnlockBlk ----------------------------------------------------------------
typedef void (ebAPI EB_UNLOCKBLK)(ebHOBJECT, _ebHSUB);
typedef EB_UNLOCKBLK *ebUNLOCKBLK;

void ebAPI ebUnlockBlk (ebHOBJECT hObject, _ebHSUB hBlk)
{
static ebUNLOCKBLK F = NULL;

	if (NULL == F) F = (ebUNLOCKBLK)GetProcAddress (g_hBScript, "ebUnlockBlk");
	F(hObject, hBlk);
}


#if defined(EBWIN32)	// ebSignal ist in WIN16 ein Macro
// ebSignal -------------------------------------------------------------------
typedef void (ebAPI EB_SIGNALPROC)(ebHOBJECT, ebBOOL);
typedef EB_SIGNALPROC *ebSIGNALPROC;

void ebAPI ebSignal (ebHOBJECT hThread, ebBOOL fBlock)
{
static ebSIGNALPROC F = NULL;

	if (NULL == F) F = (ebSIGNALPROC)GetProcAddress (g_hBScript, "ebSignal");
	F(hThread, fBlock);
}
#endif // WIN32

