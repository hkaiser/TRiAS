// Precompiled Header für Container -------------------------------------------
// File: CONTPRE.HXX

#include <bool.h>
#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
// aus Registry geladene Flags, die vorgeben, was überhaupt erlaubt ist
typedef enum tagCONTFLAGS CONTFLAG;		// forward decl
extern CONTFLAG g_rgContFlags;

#include <containr.hxx>
