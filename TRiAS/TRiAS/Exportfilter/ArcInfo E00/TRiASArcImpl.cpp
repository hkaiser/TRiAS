#include "stdafx.h"
#include "TRiASArcImpl.h"

#include <com/Errormacros2Impl.cpp>

#if defined(_DEBUG)
#pragma comment(lib,"TFrm32d.lib")
#pragma comment(lib,"TRiAS32d.lib")
#else
#pragma comment(lib,"TFrmWork.lib")
#pragma comment(lib,"Containr.lib")
//#error "Release-Libraries definieren"
#endif

#pragma warning(disable: 4273)	//warning C4273: 'lstrcmpA' : inconsistent dll linkage.  dllexport assumed.

int StrCmp (void *str1, void *str2) {
	return lstrcmp( (LPCTSTR) str1, (LPCTSTR) str2 );
}
