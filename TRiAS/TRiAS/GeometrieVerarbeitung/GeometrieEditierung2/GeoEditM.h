// Allgemeine Manifestkonstanten
// File: GeoEditM.h

#ifndef _GEOEDITM_H
#define _GEOEDITM_H


#define _GEOEDIT_EXPORT

#if defined(__GEOEDITDLL__)
#define _GEOEDIT_ENTRY	__declspec(dllexport)
#else 	// __GEOEDITDLL__
#define _GEOEDIT_ENTRY	__declspec(dllimport)
#endif	// __GEOEDITDLL__


#endif // _GEOEDITM_H
