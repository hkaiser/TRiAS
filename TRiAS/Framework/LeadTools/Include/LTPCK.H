/*
   LTPCK.H - pack header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#if !defined(FOR_LINUX) && !defined(FOR_DOTNET)

#ifdef _HEADER_ENTRY_

   #ifdef __cplusplus
      extern "C"
      {
   #endif

   #if defined(__BORLANDC__) && defined(FOR_WIN)
      #pragma option -a1
   #else
      #ifndef RC_INVOKED
         #ifdef __BORLANDC__
            #pragma warn -pck
         #else
            #pragma warning(disable: 4103)
         #endif
         #pragma pack(1)
      #endif                          /* RC_INVOKED */
   #endif                          /* __BORLANDC__ */

#elif defined(_HEADER_ENTRY_8_)

   #ifdef __cplusplus
      extern "C++"
      {
   #endif

   #if defined(__BORLANDC__) && defined(FOR_WIN)
      #pragma option -a8
   #else
      #ifndef RC_INVOKED
         #ifdef __BORLANDC__
            #pragma warn -pck
         #else
            #pragma warning(disable: 4103)
         #endif
         #pragma pack(8)
      #endif                          /* RC_INVOKED */
   #endif                          /* __BORLANDC__ */

#else

   #if defined(__BORLANDC__) && defined(FOR_WIN)
      #pragma option -a.
   #else
      #ifndef RC_INVOKED
         #pragma pack()
      #endif                          /* RC_INVOKED */
   #endif                          /* __BORLANDC__ */

   #ifdef __cplusplus
      } // extern "C"
   #endif

#endif

#elif defined(FOR_DOTNET)
   #pragma warning(disable: 4103)
   #ifdef _HEADER_ENTRY_
      #pragma pack(1)
   #else
      #pragma pack()
   #endif // _HEADER_ENTRY_
#endif   // FOR_LINUX && FOR_DOTNET
