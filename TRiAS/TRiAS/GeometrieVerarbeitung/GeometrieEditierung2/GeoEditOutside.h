// Declaration of BasicScript-Extension functions
// File: GeoEditOutside.h 
// H. Kaiser


#ifndef _GEOEDITOUTSIDE_H
#define _GEOEDITOUTSIDE_H

///////////////////////////////////////////////////////////////////////////////
// Function Prototypes 
void TRiAS_not_supported (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
//
void refcnt_geoedit (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_geoedit_AddObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_geoedit_GetObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_geoedit_RemoveObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_geoedit_AddObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_geoedit_GetObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_geoedit_RemoveObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

#endif // _GEOEDITOUTSIDE_H
