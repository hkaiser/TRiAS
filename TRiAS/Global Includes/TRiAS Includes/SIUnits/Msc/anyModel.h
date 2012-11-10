// ----------------------------------------------------------------------
//
// anyModel.h - convenience header to allow compile-time model selection
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//                                                                     \\
// NOTICE:                                                             \\
//   This file is part of "The SI Library of Unit-Based Computation."  \\
//   See "doc/README" for copyright, license, and other information.   \\
//                                                                     \\
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//
// Note:
//   After #include-ing this header, the user may select a model via a
//   command line -DUSExxxModel flag, replacing xxx by the abbreviated
//   model name
//
// History:
//   07-Sep-1998  WEB  Initial draft
//   27-Jan-1999  WEB  Added diagnostic when no USExxxModel is defined
//
// ----------------------------------------------------------------------



#if   defined USEstdModel
  #include "stdModel.h"

#elif defined USErelModel
  #include "relModel.h"

#elif defined USEhepModel
  #include "hepModel.h"

#elif defined USEqtmModel
  #include "qtmModel.h"

#elif defined USEnatModel
  #include "natModel.h"

#else
  #error "need to #define USExxxModel for desired model xxx

#endif
