// BScript-Erweiterung ------------------------------------------------------
// File: BSCREXTF.CPP

#include "bscriptp.hxx"
#include "bscrextf.h"

#include "mstrstr.hxx"
#include "mstrstr.inl"
#include "mlongstr.hxx"
#include "mlongstr.inl"

#include "ebarray.hxx"
#include "rexpstr.h"

// --------------------------------------------------------------------------
// Jump table of pointers to extension routines
// --------------------------------------------------------------------------
void (*extensions[])(ebHTHREAD hThread,int iNumArgs,ebARGS lpArgs) = {
	refcnt_MapStringString,				// 1
	func_MapStringString_Add,			// 2
	func_MapStringString_Delete,			// 3
	func_MapStringString_Item,			// 4
	func_MapStringString_Find,			// 5
	propget_MapStringString_Count,			// 6

	refcnt_MapLongString,				// 7
	func_MapLongString_Add,				// 8
	func_MapLongString_Delete,			// 9
	func_MapLongString_Item,			// 10
	func_MapLongString_Find,			// 11
	propget_MapLongString_Count,			// 12

	func_MapStringString_AddObj,			// 13

	refcnt_StringString,				// 14
	propget_StringString_Key,			// 15
	propget_StringString_Data,			// 16
	propset_StringString_Data,			// 17

	protofunc_Split,				// 18

// allgemeine StringManipulations-Funktionen
	protofunc_SplitArray,				// 19
	protofunc_Subst,				// 20
	protofunc_GSubst,				// 21
	protofunc_SubStr,				// 22
	protofunc_Match,				// 23
	protofunc_Val16,				// 24

// Koordinatentransformations-Routinen
	protocmd_GauGeoK,				// 25
	protocmd_GeoGauK,				// 26
	protocmd_GauGeoB,				// 27
	protocmd_GeoGauB,				// 28

	protocmd_SetBreakScript,		// 29
	protofunc_GetAutoStart	,		// 30
};

// ----------------------------------------------------------------------------
// refcnt_MapStringString
// ----------------------------------------------------------------------------

void refcnt_MapStringString (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
		CMapStringString *pMap = CMapStringString :: CreateInstance();
		 
			ebSetObject (lpArgs, 0, (DWORD)pMap);
		}
		break;
		
	case OBJECT_REFINC:
		((CMapStringString *)ebGetObject(lpArgs, 1)) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		((CMapStringString *)ebGetObject(lpArgs, 1)) -> Release();
		break;
	}
}


// ----------------------------------------------------------------------------
// func_MapStringString_Add
// ----------------------------------------------------------------------------

void func_MapStringString_Add (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
ebHSUB hStrKey = ebGetString (lpArgs, 2);
LPTSTR pStrKey = ebLockString (hThread, hStrKey);
ebHSUB hStrData = ebGetString (lpArgs, 3);
LPTSTR pStrData = ebLockString (hThread, hStrData);

	if (pStrKey && pStrData) {
	CMapStringString *pMap = (CMapStringString *)ebGetObject(lpArgs, 1);

		ebSetInt (lpArgs, 0, pMap -> FAddItem (pStrKey, pStrData));
	}
	if (pStrData) ebUnlockString (hThread, hStrData);
	if (pStrKey) ebUnlockString (hThread, hStrKey);
}


// ----------------------------------------------------------------------------
// func_MapStringString_AddObj
// ----------------------------------------------------------------------------

void func_MapStringString_AddObj (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CStringString *pItem = (CStringString *)ebGetObject (lpArgs, 2);

	if (pItem) {
	CMapStringString *pMap = (CMapStringString *)ebGetObject(lpArgs, 1);

		ebSetInt (lpArgs, 0, pMap -> FAddItem (pItem));
	}
}


// ----------------------------------------------------------------------------
// func_MapStringString_Delete
// ----------------------------------------------------------------------------

void func_MapStringString_Delete (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
ebHSUB hStr = ebGetString (lpArgs, 2);
LPTSTR pStr = ebLockString (hThread, hStr);

	if (pStr) {
	CMapStringString *pMap = (CMapStringString *)ebGetObject(lpArgs, 1);

		ebSetInt (lpArgs, 0, pMap -> FDeleteItem (pStr));
		ebUnlockString (hThread, hStr);
	}
}


// ----------------------------------------------------------------------------
// func_MapStringString_Item
// ----------------------------------------------------------------------------

void func_MapStringString_Item (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
ebHSUB hStr = ebGetString (lpArgs, 2);
LPTSTR pStr = ebLockString (hThread, hStr);

	if (pStr) {
	CMapStringString *pMap = (CMapStringString *)ebGetObject(lpArgs, 1);
	CStringString *pItem = pMap -> FFindItem (pStr);

		ebFreeString (hThread, ebGetString (lpArgs, 0));
		ebSetString (lpArgs, 0, NULL);
		if (pItem) 
			ebSetString (lpArgs, 0, ebCreateString (hThread, pItem -> FGetData()));
		ebUnlockString (hThread, hStr);
	}
}


// ----------------------------------------------------------------------------
// func_MapStringString_Find
// ----------------------------------------------------------------------------

void func_MapStringString_Find (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
ebHSUB hStr = ebGetString (lpArgs, 2);
LPTSTR pStr = ebLockString (hThread, hStr);

	if (pStr) {
	CMapStringString *pMap = (CMapStringString *)ebGetObject(lpArgs, 1);
	CStringString *pItem = pMap -> FFindItem (pStr);
	CStringString *pOldItem = (CStringString *)ebGetObject (lpArgs, 0);

		if (pOldItem) pOldItem -> Release();

		pItem -> AddRef();
		ebSetObject (lpArgs, 0, (DWORD)pItem);
	}
}


// ----------------------------------------------------------------------------
// propget_MapStringString_Count
// ----------------------------------------------------------------------------

void propget_MapStringString_Count (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	ebSetLong (lpArgs, 0, ((CMapStringString *)ebGetObject(lpArgs, 1)) -> Count());
}


// ----------------------------------------------------------------------------
// refcnt_MapLongString
// ----------------------------------------------------------------------------

void refcnt_MapLongString (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
		CMapLongString *pMap = CMapLongString :: CreateInstance();
		 
			ebSetObject (lpArgs, 0, (DWORD)pMap);
		}
		break;
		
	case OBJECT_REFINC:
		((CMapLongString *)ebGetObject(lpArgs, 1)) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		((CMapLongString *)ebGetObject(lpArgs, 1)) -> Release();
		break;
	}
}


// ----------------------------------------------------------------------------
// func_MapLongString_Add
// ----------------------------------------------------------------------------

void func_MapLongString_Add (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
LONG lKey = ebGetLong (lpArgs, 2);
ebHSUB hStrData = ebGetString (lpArgs, 3);
LPTSTR pStrData = ebLockString (hThread, hStrData);

	if (pStrData) {
	CMapLongString *pMap = (CMapLongString *)ebGetObject(lpArgs, 1);

		ebSetInt (lpArgs, 0, pMap -> FAddItem (lKey, pStrData));
		
		ebUnlockString (hThread, hStrData);
	}
}


// ----------------------------------------------------------------------------
// func_MapLongString_Delete
// ----------------------------------------------------------------------------

void func_MapLongString_Delete (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
LONG lKey = ebGetLong (lpArgs, 2);
CMapLongString *pMap = (CMapLongString *)ebGetObject(lpArgs, 1);

	ebSetInt (lpArgs, 0, pMap -> FDeleteItem (lKey));
}


// ----------------------------------------------------------------------------
// func_MapLongString_Item
// ----------------------------------------------------------------------------

void func_MapLongString_Item (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
LONG lKey = ebGetLong (lpArgs, 2);
CMapLongString *pMap = (CMapLongString *)ebGetObject(lpArgs, 1);
CLongString *pItem = pMap -> FFindItem (lKey);

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	ebSetString (lpArgs, 0, NULL);
	if (pItem) 
		ebSetString (lpArgs, 0, ebCreateString (hThread, pItem -> FGetData()));
}


// ----------------------------------------------------------------------------
// func_MapLongString_Find
// ----------------------------------------------------------------------------

void func_MapLongString_Find (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
LONG lKey = ebGetLong (lpArgs, 2);
CMapLongString *pMap = (CMapLongString *)ebGetObject(lpArgs, 1);
CLongString *pItem = pMap -> FFindItem (lKey);

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	ebSetString (lpArgs, 0, NULL);
	if (pItem) 
		ebSetString (lpArgs, 0, ebCreateString (hThread, pItem -> FGetData()));
}


// ----------------------------------------------------------------------------
// propget_MapLongString_Count
// ----------------------------------------------------------------------------

void propget_MapLongString_Count (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	ebSetLong (lpArgs, 0, ((CMapLongString *)ebGetObject(lpArgs, 1)) -> Count());
}


// ----------------------------------------------------------------------------
// refcnt_StringString
// ----------------------------------------------------------------------------

void refcnt_StringString (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		ebSetObject (lpArgs, 0, NULL);
		break;
		
	case OBJECT_REFINC:
		((CStringString *)ebGetObject(lpArgs, 1)) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		((CStringString *)ebGetObject(lpArgs, 1)) -> Release();
		break;
	}
}


// ----------------------------------------------------------------------------
// propget_StringString_Key
// ----------------------------------------------------------------------------

void propget_StringString_Key (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CStringString *pItem = (CStringString *)ebGetObject (lpArgs, 2);

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	ebSetString (lpArgs, 0, NULL);
	if (pItem) 
		ebSetString (lpArgs, 0, ebCreateString (hThread, pItem -> FGetLPCTSTR()));
}


// ----------------------------------------------------------------------------
// propget_StringString_Data
// ----------------------------------------------------------------------------

void propget_StringString_Data (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CStringString *pItem = (CStringString *)ebGetObject (lpArgs, 2);

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	ebSetString (lpArgs, 0, NULL);
	if (pItem) 
		ebSetString (lpArgs, 0, ebCreateString (hThread, pItem -> FGetData()));
}


// ----------------------------------------------------------------------------
// propset_StringString_Data
// ----------------------------------------------------------------------------

void propset_StringString_Data (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CStringString *pItem = (CStringString *)ebGetObject (lpArgs, 2);
ebHSUB hStr = ebGetString (lpArgs, 2);
LPTSTR pStr = ebLockString (hThread, hStr);

	if (pItem && pStr)
		pItem -> FSetData (pStr);

	if (pStr) ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// protofunc_Split
// ----------------------------------------------------------------------------

void protofunc_Split (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
ebHSUB hLine = ebGetString (lpArgs, 1);
LPTSTR pLine = ebLockString (hThread, hLine);
ebHSUB hSep = ebGetString (lpArgs, 2);
LPTSTR pSep = ebLockString (hThread, hSep);

	if (pLine && pSep) {
	LPTSTR pFound = strpbrk (pLine, pSep);
	CStringString *pItem = (CStringString *)ebGetObject (lpArgs, 0);

		if (pItem) pItem -> Release();
		ebSetObject (lpArgs, 0, NULL);
		if (pFound == NULL) // Separator nicht gefunden
			pItem = new CStringString (pLine, "");
		else {
		string strT (pLine, pFound-pLine);

			pItem = new CStringString (strT.c_str(), pFound+1);
		}
		ebSetObject (lpArgs, 0, (DWORD)pItem);
	}
	if (pLine) ebUnlockString (hThread, hLine);
	if (pSep) ebUnlockString (hThread, hSep);
}


// ----------------------------------------------------------------------------
// protofunc_Split
//
// i% = split(str$,a$(),rex$) 
// split str$ by regular expression rex$ and save elements in stringarray a$()
//
// ----------------------------------------------------------------------------
DeclareEbLock(ebHSUB);		// ebARRAY-Zugriff


void protofunc_SplitArray (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
ebHSUB hLine = ebGetString (lpArgs, 1);
LPTSTR pLine = ebLockString (hThread, hLine);
ebHSUB hSep = ebGetString (lpArgs, 3);
LPTSTR pSep = ebLockString (hThread, hSep);	// SeparatorZeichen

	if (pSep == NULL || pLine == NULL) {
		ebSetInt (lpArgs, 0, 0);
		if (pLine) ebUnlockString (hThread, hLine);
		if (pSep) ebUnlockString (hThread, hSep);
		return;
	}

// Feststellen, wie viele Elemente das Feld haben wird
CRegExpString RE (pSep);
LPTSTR pFound = pLine;
int iCnt = 1;

	while (RE.Index (pFound)) {
		iCnt++;
		pFound = RE.MatchEnd();
	}

// Array redimensionieren, Strings in Array einfügen
CEbArray eba (hThread, ebGetArray (lpArgs, 2));

	if (eba.ReDim (iCnt)) {
	CEbLockebHSUB ebs (eba);

		if (!(!ebs)) {
		ebHSUB *pStrs = (ebHSUB *)ebs;
		string strT;
					
			pFound = pLine;
			for (int i = 0; i < iCnt && pFound; i++) {
			LPTSTR pLast = NULL;
			LPTSTR pFirst = NULL;

				if ((pFirst = RE.Index (pFound, &pLast)) != NULL) {
					strT = string (pFound, pFirst-pFound);
					pFound = pLast;
				} else {
					strT = string (pFound);
					pFound = NULL;
				}
				ebFreeString (hThread, pStrs[i]);
				pStrs[i] = ebCreateString (hThread, strT.c_str());
			}
		}
	}

	ebSetInt (lpArgs, 0, iCnt);

	ebUnlockString (hThread, hLine);
	ebUnlockString (hThread, hSep);
}


// ----------------------------------------------------------------------------
// protofunc_Subst
//
// i% = Subst(replace$,search$,str$) substitute search$ for 1st replace$ in str$
//		search$ is a regular expression
//		returns 0 or 1: number of substitutions
//
// ----------------------------------------------------------------------------

void protofunc_Subst (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
ebHSUB hRepl = ebGetString (lpArgs, 1);
LPTSTR pRepl = ebLockString (hThread, hRepl);	// neuer Text
ebHSUB hSearch = ebGetString (lpArgs, 2);
LPTSTR pSearch = ebLockString (hThread, hSearch);// SuchText (REX)
ebHSUB hStr = ebGetString (lpArgs, 3);
LPTSTR pStr = ebLockString (hThread, hStr);	// zu bearbeitendes String

// Parameter validieren
	if (pRepl == NULL || pSearch == NULL || pStr == NULL) {
		ebSetInt (lpArgs, 0, 0);
		if (pRepl) ebUnlockString (hThread, hRepl);
		if (pSearch) ebUnlockString (hThread, hSearch);
		if (pStr) ebUnlockString (hThread, hStr);
		return;
	}

// matching
CRegExpString RE (pSearch);
int iFound = 0;
LPTSTR pFirst = NULL;
LPTSTR pLast = NULL;

	if ((pFirst = RE.Index (pStr, &pLast)) != NULL) {
	string strT (pStr, pFirst - pStr);

		strT += pRepl;
		strT += pLast;

		ebUnlockString (hThread, hStr);
		ebFreeString (hThread, hStr);
		ebSetString (lpArgs, 3, ebCreateString (hThread, strT.c_str())); 
		iFound = 1;
	} else
		ebUnlockString (hThread, hStr);

	ebSetInt (lpArgs, 0, iFound);

	ebUnlockString (hThread, hRepl);
	ebUnlockString (hThread, hSearch);
}


// ----------------------------------------------------------------------------
// protofunc_GSubst
//
// i% = Subst(replace$,search$,str$) substitute global search$ for replace$ in str$
//		search$ is a regular expression
//		returns number of substitutions
//
// ----------------------------------------------------------------------------

void protofunc_GSubst (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
ebHSUB hRepl = ebGetString (lpArgs, 1);
LPTSTR pRepl = ebLockString (hThread, hRepl);	// neuer Text
ebHSUB hSearch = ebGetString (lpArgs, 2);
LPTSTR pSearch = ebLockString (hThread, hSearch);// SuchText (REX)
ebHSUB hStr = ebGetString (lpArgs, 3);
LPTSTR pStr = ebLockString (hThread, hStr);	// zu bearbeitendes String

// Parameter validieren
	if (pRepl == NULL || pSearch == NULL || pStr == NULL) {
		ebSetInt (lpArgs, 0, 0);
		if (pRepl) ebUnlockString (hThread, hRepl);
		if (pSearch) ebUnlockString (hThread, hSearch);
		if (pStr) ebUnlockString (hThread, hStr);
		return;
	}

// matching
CRegExpString RE (pSearch);
int iFound = 0;
LPTSTR pFirst = NULL;
LPTSTR pLast = NULL;
string strT;

	while ((pFirst = RE.Index (pStr, &pLast)) != NULL) {
		strT += string (pStr, pFirst - pStr);
		strT += pRepl;

		iFound++;
		pStr = pLast;
	}
	strT += pStr;

	ebUnlockString (hThread, hStr);
	if (iFound) {
		ebFreeString (hThread, hStr);
		ebSetString (lpArgs, 3, ebCreateString (hThread, strT.c_str())); 
	}

	ebSetInt (lpArgs, 0, iFound);

	ebUnlockString (hThread, hRepl);
	ebUnlockString (hThread, hSearch);
}


// ----------------------------------------------------------------------------
// protofunc_SubStr
//
// result$ = SubStr$(str$,begin%,num%)	retrieves substring of str$, beginning 
//		at index begin% of length num%
//
// ----------------------------------------------------------------------------

void protofunc_SubStr (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
ebHSUB hStr = ebGetString (lpArgs, 1);
string strT = ebLockString (hThread, hStr);	// zu untersuchender String
int iBegin = ebGetInt (lpArgs, 2) - 1;		// erstes Zeichen
int iNum = iNumArgs > 2 ? ebGetInt (lpArgs, 3) : NPOS;		// Anzahl der Zeichen

	ebUnlockString (hThread, hStr);
	strT = strT.substr (iBegin, (uint)iNum > strT.length() ? NPOS : iNum);
	ebFreeString (hThread, ebGetString (lpArgs, 0));
	ebSetString (lpArgs, 0, ebCreateString (hThread, strT.c_str()));
}


// ----------------------------------------------------------------------------
// protofunc_Match
//
// index% = Match(search$,str$)	matches search$ in str$ and 
//				returns index% or 0, when not found
//
// ----------------------------------------------------------------------------

void protofunc_Match (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
ebHSUB hStr = ebGetString (lpArgs, 1);
LPTSTR pStr = ebLockString (hThread, hStr);	// zu bearbeitendes String
ebHSUB hSearch = ebGetString (lpArgs, 2);
LPTSTR pSearch = ebLockString (hThread, hSearch);	// SuchText

// Parameter validieren
	if (pSearch == NULL || pStr == NULL) {
		ebSetInt (lpArgs, 0, 0);
		if (pSearch) ebUnlockString (hThread, hSearch);
		if (pStr) ebUnlockString (hThread, hStr);
		return;
	}

// matching
CRegExpString RE (pSearch);
LPTSTR pFirst = RE.Index (pStr);
int iPos = pFirst ? pFirst - pStr : -1;

	ebSetInt (lpArgs, 0, iPos + 1);
	ebUnlockString (hThread, hSearch);
	ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// protofunc_Val16
//
// lValue& = Val16(str$)
//
// ----------------------------------------------------------------------------

void protofunc_Val16 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
ebHSUB hStr = ebGetString (lpArgs, 1);
LPTSTR pStr = ebLockString (hThread, hStr);	// zu bearbeitendes String
unsigned long lValue = strtoul (pStr, NULL, 16);

	ebSetLong (lpArgs, 0, lValue);
	ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// protocmd_GauGeoK: Gauß/Krüger in geodätische Koordinaten umrechnen
//		     Bezugsellipsoid: Krassovski
//
// GauGeoK Meridian%, StrBreite%, HWert#, RWert#, XKoord#, YKoord#
//			(HWert,RWert) --> (XWert,YWert)
//
// ----------------------------------------------------------------------------
extern "C"
void PASCAL gaugeo (double ha, double hb, short strbr, short l0, 
		    double Hwert, double Rwert, 
		    long double *Breite, long double *Laenge);
extern "C"
void PASCAL geogau (double ha, double hb, short strbr, short l0, 
		    double Breite, double Laenge, 
		    long double *Hwert, long double *Rwert);


void protocmd_GauGeoK (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
short iM = ebGetInt (lpArgs, 1);
short iStr = ebGetInt (lpArgs, 2);
double dH = ebGetDouble (lpArgs, 3);
double dR = ebGetDouble (lpArgs, 4);
long double ldX, ldY;

	gaugeo (6378245.0, 6356863.01877, iStr, iM, dH, dR, &ldY, &ldX);
	ebSetDouble (lpArgs, 5, double(ldX));
	ebSetDouble (lpArgs, 6, double(ldY));
}


// ----------------------------------------------------------------------------
// protocmd_GeoGauK: geodätische Koordinaten in Gauß/Krüger umrechnen
//		     Bezugsellipsoid: Krassovski
//
// GeoGauK Meridian%, StrBreite%, XKoord#, YKoord#, HWert#, RWert#
//			(XWert,YWert) --> (HWert,RWert)
//
// ----------------------------------------------------------------------------

void protocmd_GeoGauK (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
short iM = ebGetInt (lpArgs, 1);
short iStr = ebGetInt (lpArgs, 2);
double dX = ebGetDouble (lpArgs, 3);
double dY = ebGetDouble (lpArgs, 4);
long double ldR, ldH;

	geogau (6378245.0, 6356863.01877, iStr, iM, dY, dX, &ldH, &ldR);
	ebSetDouble (lpArgs, 5, double(ldH));
	ebSetDouble (lpArgs, 6, double(ldR));
}


// ----------------------------------------------------------------------------
// protocmd_GauGeoB: Gauß/Krüger in geodätische Koordinaten umrechnen
//		     Bezugsellipsoid: Bessel
//
// GauGeoK Meridian%, StrBreite%, HWert#, RWert#, XKoord#, YKoord#
//			(HWert,RWert) --> (XWert,YWert)
//
// ----------------------------------------------------------------------------

void protocmd_GauGeoB (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
short iM = ebGetInt (lpArgs, 1);
short iStr = ebGetInt (lpArgs, 2);
double dH = ebGetDouble (lpArgs, 3);
double dR = ebGetDouble (lpArgs, 4);
long double ldX, ldY;

	gaugeo (6377397.155, 6356078.96325, iStr, iM, dH, dR, &ldY, &ldX);
	ebSetDouble (lpArgs, 5, double(ldX));
	ebSetDouble (lpArgs, 6, double(ldY));
}


// ----------------------------------------------------------------------------
// protocmd_GeoGauB: geodätische Koordinaten in Gauß/Krüger umrechnen
//		     Bezugsellipsoid: Bessel
//
// GeoGauB Meridian%, StrBreite%, XKoord#, YKoord#, HWert#, RWert#
//			(XWert,YWert) --> (HWert,RWert)
//
// ----------------------------------------------------------------------------

void protocmd_GeoGauB (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
short iM = ebGetInt (lpArgs, 1);
short iStr = ebGetInt (lpArgs, 2);
double dX = ebGetDouble (lpArgs, 3);
double dY = ebGetDouble (lpArgs, 4);
long double ldR, ldH;

	geogau (6377397.155, 6356078.96325, iStr, iM, dY, dX, &ldH, &ldR);
	ebSetDouble (lpArgs, 5, double(ldH));
	ebSetDouble (lpArgs, 6, double(ldR));
}

// ----------------------------------------------------------------------------
// protocmd_SetBreakScript
// ----------------------------------------------------------------------------
void protocmd_SetBreakScript (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
long l = ebGetLong(lpArgs, 1);
	ebThread_SetLong (hThread, 0, l);
}

// ----------------------------------------------------------------------------
// protofunc_GetAutoStart	
// ----------------------------------------------------------------------------
void protofunc_GetAutoStart	(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
long lValue = ebThread_GetLong (hThread, 4);
	ebSetLong (lpArgs, 0, lValue);
}

// --------------------------------------------------------------------------
// This routine is the entry point used by the EBRUN.DLL module to execute 
// an external routine.
//
// parameters:	hThread		pointer to reserved structure
//			wCmdNum		ID of the extension routine as it appears in the
//						prototype table
//			iNumArgs	number of arguments passed to this routine
//			lpArgs		pointer to an array of pointers to the arguments
//
// returns:		nothing
// --------------------------------------------------------------------------
extern "C"
void ebCALLBACK _XTENSN_EXPORT RuntimeCallback(ebHTHREAD hThread,WORD wCmdNum,int iNumArgs,ebARGS lpArgs)
{
// call the extension routine via the jump table
	(*extensions[wCmdNum - 1])(hThread,iNumArgs,lpArgs);
}


// --------------------------------------------------------------------------
// Init - this routine is called when the DLL is loaded. If this routien
// returns FALSE, then the extension will not be loaded. 
//
// parameters:	none
//
// returns:		true		success initializing
//			false		unable to initialize
// --------------------------------------------------------------------------
#if defined(WIN32)
#define LOADLIBRARY_FAILED(x) (x == 0)
#else
#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#endif
extern "C"
bool _XTENSN_EXPORT ebCALLBACK Init (ebHINSTANCE hInst)
{
	return true;
}

// --------------------------------------------------------------------------
// This function is called immediately before the extension DLL is removed
// from memory. It can perform any cleanup that the DLL may need to perform.
// --------------------------------------------------------------------------
extern "C"
void _XTENSN_EXPORT ebCALLBACK Term (ebHINSTANCE hInst)
{
}

