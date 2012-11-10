//-----------------------------------------------------------------
// File name:  DLLFLOAT.CXX
//
//      This DLL uses a function ConvertFltToStr() to convert a float
//      to a string. Since the C 6.00 run-time functions do not support
//      converting a float to a string inside a DLL, it was necessary to
//      write a function to perform this task.  A DLL that needs to
//      perform such a conversion should incorporate ConvertFltToStr().
//        
//      To get the mantissa and the exponent of the float,
//      ConvertFltToStr() calls the C run-time function frexp().  But
//      due to a bug this call does not work in small and medium
//      model DLLs. Therefore, it was necessary to write a version
//      of frexp(), called MYfrexp. 
//
// This is the main DLL source file.  It contains LibMain, the DLL's 
// entry point.
//
// Description of functions:
//
//    LibMain     -     This DLL's entry point.  Analogous to WinMain.
//    DLLFunc     -     A function exported by this DLL for use by
//                      applications.
//
//
// Written by Microsoft Product Support Services, Windows Developer Support.
//
// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//
// -----------------------------------------------------------------

#include "StdAfx.h"

// -----------------------------------------------------------------
//
// ConvertFltToStr ()
//
// Purpose: This function demonstrates conversion from a float to a
//          string within a DLL.  
//
// Parameters: double  dblFloat    -  Float passed by the calling app.
//             LPSTR   DllStr      -  String to contain the converted value.
//
// Return Value:  None.
// -----------------------------------------------------------------

extern "C"
LPSTR PASCAL DtoACTF /*ConvertFltToStr*/ (LPSTR lpszString, LPSTR lpszFormat, int iPrec, double dblFloat)
{

  //  BIG_NUMBER determines how many decimal places the conversion will use
  //  (i.e. 1000000 = 6 places, 10000000 = 7 places, etc.)
  //	If you wish to expand the precision you will also need to change
  //  the .%06 precision argument used in the wsprintf() statements at the
  //  end of this function.
//#define BIG_NUMBER              1000000     
#define LOG_OF_2                0.301029995

   static int nExponent;
   static double dblInt;
   static double dblFraction;

   double dblTempNumber;
   double dblMantissa;

   unsigned long ulTempFraction;
   int nDesired10Power;

   double BIG_NUMBER = 1.0;

	for (int i = 0; i < iPrec; i++)
		BIG_NUMBER *= 10;

   // Get the fractional part and the integer part of the float
   dblFraction = modf(dblFloat, &dblInt);
   
   // If exponent is too big or too small, 
   // then show the float in scientific notation
   if ((fabs(dblFloat) > 1E10 || fabs(dblFloat) < 1E-10) && dblFloat)
   {
      // Convert the exponent from base 2 to base 10
      dblMantissa = frexp(dblFloat, &nExponent);
      nDesired10Power = (int)(LOG_OF_2 * nExponent);
      dblTempNumber = dblMantissa * pow(2, nExponent) / pow(10, nDesired10Power);
      if (dblFloat<0)
          dblTempNumber = -dblTempNumber;
      dblFraction = modf(dblTempNumber, &dblInt);
   }

   dblFraction = fabs(dblFraction) * BIG_NUMBER;
   ulTempFraction = (unsigned long)dblFraction;

   
   // Perform rounding.  We will round up if the discarded portion
   // of the fraction is greater or equal to 0.5.
   if (dblFraction - (double)ulTempFraction >= 0.5)
      ulTempFraction++;

   // We don't want to display the exponent if it is zero
   if ((fabs(dblFloat) > 1E10 || fabs(dblFloat) < 1E-10) && dblFloat)
      wsprintf(lpszString, "%ld.%06luE%d", (long)dblInt, ulTempFraction, nDesired10Power);
   else
      // The float can be shown without scientific notation
      wsprintf(lpszString, lpszFormat /*"%ld.%06lu"*/, (long)dblInt, ulTempFraction);

return lpszString;
}


