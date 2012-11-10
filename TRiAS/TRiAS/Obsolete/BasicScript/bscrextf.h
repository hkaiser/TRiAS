// BScript-Erweiterung ------------------------------------------------------
// File: BSCREXTF.CPP

#if !defined(_BSCREXTF_H)
#define _BSCREXTF_H

void refcnt_MapStringString (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_MapStringString_Add (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_MapStringString_Delete (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_MapStringString_Item (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_MapStringString_Find (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_MapStringString_Count (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_MapStringString_AddObj (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
                   
void refcnt_MapLongString (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_MapLongString_Add (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_MapLongString_Delete (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_MapLongString_Item (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_MapLongString_Find (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_MapLongString_Count (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void refcnt_StringString (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_StringString_Key (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_StringString_Data (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_StringString_Data (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void protofunc_Split (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void protofunc_SplitArray (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void protofunc_Subst (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void protofunc_GSubst (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void protofunc_SubStr (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void protofunc_Match (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void protofunc_Val16 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void protocmd_GauGeoK (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void protocmd_GeoGauK (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void protocmd_GauGeoB (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void protocmd_GeoGauB (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void protocmd_SetBreakScript (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void protofunc_GetAutoStart	 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

#endif // _BSCREXTF_H
                  
