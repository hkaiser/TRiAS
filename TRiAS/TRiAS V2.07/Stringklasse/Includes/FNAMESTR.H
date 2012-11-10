// Zusätzliche Funktionen für FileName-Handling -------------------------------
// File: FNAMESTR.H

#if !defined(_FNAMESTR_H)
#define _FNAMESTR_H

#if _MSC_VER <= 1020
string get_drive (const string &str);
string get_path (const string &str);
string get_name (const string &str);
string get_ext (const string &str);
#else

inline string get_drive (const string &str)
{
char cbDrive[_MAX_DRIVE];
string drive;

	if ('\\' != str[0] || '\\' != str[1])	// UNC's beachten
		_splitpath (str.c_str(), cbDrive, NULL, NULL, NULL);

	drive = cbDrive;
	return drive;
}

inline string get_path (const string &str)
{
char cbPath[_MAX_PATH];
string path;

	_splitpath (str.c_str(), NULL, cbPath, NULL, NULL);
	
	path = cbPath;
	return path;
}

inline string get_name (const string &str)
{
char cbName[_MAX_FNAME];
string name;

	_splitpath (str.c_str(), NULL, NULL, cbName, NULL);
	
	name = cbName;
	return name;
}

inline string get_ext (const string &str)
{
char cbExt[_MAX_EXT];
string ext;

	_splitpath (str.c_str(), NULL, NULL, NULL, cbExt);
	
	ext = cbExt;
	return ext;
}

#endif // _MSC_VER

#endif // _FNAMESTR_H


