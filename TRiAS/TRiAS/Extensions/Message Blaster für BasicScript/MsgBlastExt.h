// MsgBlastExt.h: Declaration of BasicScript-Extension functions

#if !defined(_MSGBLASTEXT_H)
#define _MSGBLASTEXT_H

///////////////////////////////////////////////////////////////////////////////
// Function Prototypes 
void TRiAS_not_supported (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
//
void refcnt_MessageMap (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_MessageMap_Enabled (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_MessageMap_Enabled (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_MessageMap_HasMsg (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_MessageMap_ToCall (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_MessageMap_ToCall (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_MessageMap_RemoveAll (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_MessageMap_RemoveMessage (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_MessageMap_AddMessage (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void refcnt_Mouse (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Mouse_GetLastKey (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propfunc_Mouse_GetPoint (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propfunc_Mouse_GetPointDrag (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

#endif // _MSGBLASTEXT_H
