#include <iostream.h>
#include <afxwin.h>
#include <afxcmn.h>			// Win32 Common Controls

#include <afxtempl.h>

#include "lmfcx/lafxwin.h"
#include "lpict/pictdef.h"
#include "lpict/picture.h"
#include "lpict/PictFlt.h"

#if defined(_DEBUG)
	#define IMPORT_PICT_DLL "lpict42d.lib"
#elif defined(_RDEBUG)
	#define IMPORT_PICT_DLL "lpict42r.lib"
#else
	#define IMPORT_PICT_DLL "lpict42.lib"
#endif
