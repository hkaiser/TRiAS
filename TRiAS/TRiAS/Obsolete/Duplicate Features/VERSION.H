// Version dieser Erweiterung -------------------------------------------------
// File: VERSION.H

#if !defined(_VERSION_H)
#define _VERSION_H

#if defined(WIN32)
#include "win32/versio32.h"
#else
#include "versio16.h"
#endif

#endif // _VERSION_H
