// ColorsExt.h: Declaration of BasicScript-Extension functions

#if !defined(_COLORSEXT_H)
#define _COLORSEXT_H

///////////////////////////////////////////////////////////////////////////////
// Function Prototypes 
void TRiAS_not_supported (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// DoubleColor
void refcnt_DoubleColor (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void DoubleColor_RGB_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_RGB_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void DoubleColor_Red_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Green_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Blue_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Hue_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Saturation_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Brightness_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void DoubleColor_Red_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Green_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Blue_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Hue_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Saturation_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Brightness_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void DoubleColor_Complement_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Saturated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Grayed_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_Pure_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void DoubleColor_InitRGB_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DoubleColor_InitHSB_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// ColorLookUp
void refcnt_ColorLookUp (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void ColorLookUp_Init_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void ColorLookUp_GetColor_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

#endif // _COLORSEXT_H
