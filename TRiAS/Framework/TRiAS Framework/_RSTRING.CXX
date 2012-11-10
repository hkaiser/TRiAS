/* $Header:   G:/cv.win/pvcs/commonvu/src/_rstring.cxv   3.0.1.0   14 Jul 1992 11:56:04   RONAN  $
 *
 *	_ r s t r i n g . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	0.0	ferg	05oct88	-------- Milestone 2 Beta 2 .. shipped. --------
 *	0.1	ferg	02nov88	renamed from restring.cxx to _rstring.cxx, minor
 *						change to pick up AppInst from DLL.
 *	0.2	rs		06nov88	added restring dtor.
 *	0.3 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.4 jk		02dec88 Fast Compile defines added.
 *  0.5 rs      08mar89 ResId's
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.2 rs		07feb90	Use GetCurrentTask instead of _AppFind if only
 *						Handle to App is required.
 */
//  09.06.93 A.D. uve Potsdam: inline ResID::ResID(uint) ersetzt.

#include "tfrmpre.hxx"

_DLLENTRY ResString::   ResString (ResID index, uint len)
{
	string	= new char[(len ? len : 1)];
	
   	length	= LoadString (CV_RunTime :: ResID_handle(index, _AppImpFind(), RT_STRING),
   							(uint)index, string, len);
	if (length <= 0)
	{
#if defined(_DEBUG)
	DWORD dwErr = ::GetLastError();
#endif // _DEBUG
		delete string;
		string = new char[7];
		lstrcpy (string, "");
	}
}	// End of "ResString" CONSTRUCTOR

_DLLENTRY ResString:: ResString (const ResString& copy )
{
	string = 0;
	if (copy.string && (string = new char [lstrlen (copy.string) + 1]))
		lstrcpy (string, copy.string);
}

ResString&  _DLLENTRY ResString :: operator= (const ResString &copy)
{
	if (string) {
		delete string;
		string = 0;
	}
	if (copy.string && (string = new char [lstrlen(copy.string ) + 1]))
		lstrcpy (string, copy.string);

return (*this);
}

														// * 0.2 Begin *
_DLLENTRY ResString::   ~ResString ()
{
        delete string;
}
														// * 0.2 End *


/*********************************************************************
 *
 * New functions for managing resources from within resource files.
 *
 ********************************************************************/
#if !defined(WIN16)
#define LOADLIBRARY_FAILED(x) (x == 0)
#else
#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#endif

ResFile_Imp :: ResFile_Imp (const char *name, ResourceFile *pReq)
	     : m_pReq (pReq)
{
// #HK990625 work around WinNT4 LoadProcess bug
char szModuleShort[_MAX_PATH];
string strLong (name);
int cbShortName = GetShortPathName (strLong.c_str(), szModuleShort, _MAX_PATH);
LPCSTR pcModule = NULL;

	if (cbShortName != _MAX_PATH) {
		pcModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? strLong.c_str() : szModuleShort;
		hLib = ::LoadLibrary (pcModule);
	}

	if (LOADLIBRARY_FAILED (hLib)) {
	char buffer[2*_MAX_PATH];

		hLib = 0;
		wsprintf (buffer, "Application couldn't load resource %.30s", name);
		MessageBox (0, buffer, "TRiAS®-Framework", MB_TASKMODAL | MB_ICONHAND | MB_OK);
	} 
	else if (m_pReq) {
	// ResourceFile in Kette dieser Applikation einhängen
	pApp_Imp pAppImpInst = _AppImpFind();

		if (pAppImpInst) 
			pAppImpInst -> ResourceList() -> Insert ((HANDLE)hLib, m_pReq);
	}
}

ResFile_Imp :: ~ResFile_Imp (void)
{
	if (hLib) {
		if (m_pReq) {
		pApp_Imp pAppImpInst = _AppImpFind();

			if (pAppImpInst) 	// hInst aus Kette entfernen
				pAppImpInst -> ResourceList() -> Delete ((HANDLE)hLib, m_pReq);
		}
		FreeLibrary (hLib);
	}
}

_DLLENTRY ResourceFile :: ResourceFile (const char * name, BOOL fInsert)
{
	resFile_Imp = new ResFile_Imp (name, fInsert ? this : NULL);
}

_DLLENTRY ResourceFile :: ~ResourceFile (void)
{
	delete resFile_Imp;
}

// Ersatz fuer den gestrichenen Inline-Konstruktor
_DLLENTRY ResID :: ResID ( uint i ) : CvID(i)
{
	src = 0;
}
//----------------A.D.--09.06.93------------------

_DLLENTRY ResID :: ResID ( uint i, ResourceFile * source)  : CvID(i)
{
	if (source)
		src = CV_RunTime :: pResFile_to_pImp(source) -> Handle();
	else
		src = 0;
}

_DLLENTRY ResID :: ResID ( const char* s, ResourceFile * source)  : CvID(s)
{
	if (source)
		src = CV_RunTime :: pResFile_to_pImp(source) -> Handle();
	else
		src = 0;
}

CvID :: CvID (const char* s)
{
int len;

	if (s && (len = lstrlen(s))) {
		if (s[0]=='#') 
			id = atoi (&s[1]);
		else if ((len > 3) && (s[0] == 'C') && (s[1] == 'V') && (s[2] == '_'))
			id = atoi (&s[3]);
	}
	else
		str = s;
	id = 0;
}




