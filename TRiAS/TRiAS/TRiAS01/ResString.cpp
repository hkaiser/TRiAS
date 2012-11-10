// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/08/1998 12:32:22 PM
//
// @doc
// @module ResString.cpp | Description goes here

#include "trias01p.hxx"

ResString::ResString (ResID index, uint len)
{
	TX_TRY(string = new char[(len ? len : 1)]);
	if (NULL == index.Handle())
		length	= LoadString (::GetModuleHandle(NULL), (uint)index, string, len);
   	else
		length	= LoadString (index.Handle(), (uint)index, string, len);

	if (length <= 0) {
#if defined(_DEBUG)
	DWORD dwErr =::GetLastError();
#endif // _DEBUG
		delete string;
		string = new char[7];
		lstrcpy (string, "");
	}
}	// End of "ResString" CONSTRUCTOR

ResString::ResString (unsigned int iResID, uint len)
{
	TX_TRY(string = new char[(len ? len : 1)]);
	length	= LoadString (::GetModuleHandle(NULL), iResID, string, len);

	if (length <= 0) {
#if defined(_DEBUG)
	DWORD dwErr =::GetLastError();
#endif // _DEBUG
		delete string;
		string = new char[7];
		lstrcpy (string, "");
	}
}	// End of "ResString" CONSTRUCTOR

ResString::ResString (const ResString& copy)
{
	string = 0;
	if (copy.string && (string = new char [lstrlen (copy.string) + 1]))
		lstrcpy (string, copy.string);
}

ResString&  ResString::operator= (const ResString &copy)
{
	if (string) {
		delete string;
		string = 0;
	}
	if (copy.string && (string = new char [lstrlen(copy.string ) + 1]))
		lstrcpy (string, copy.string);

	return (*this);
}

ResString::~ResString ()
{
	if (string) delete string;
}

///////////////////////////////////////////////////////////////////////////////
// New functions for managing resources from within resource files.
#if !defined(WIN16)
#define LOADLIBRARY_FAILED(x) (x == 0)
#else
#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#endif

ResourceFile::ResourceFile (const char * name)
	: hLib(NULL)
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

		hLib = NULL;
		wsprintf (buffer, "Application couldn't load resource %.30s", name);
		MessageBox (0, buffer, "TRiAS®-Framework", MB_TASKMODAL | MB_ICONHAND | MB_OK);
	} 
}

ResourceFile::~ResourceFile (void)
{
	if (hLib) {
		::FreeLibrary (hLib);
		hLib = NULL;
	}
}

CvID::CvID (const char* s)
{
int len;

	if (s && (len = lstrlen(s))) {
		if (s[0] == '#') 
			id = atoi (&s[1]);
		else if ((len > 3) && (s[0] == 'C') && (s[1] == 'V') && (s[2] == '_'))
			id = atoi (&s[3]);
	}
	else
		str = s;
	id = 0;
}
