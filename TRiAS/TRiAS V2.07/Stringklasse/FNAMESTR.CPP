// Zusätzliche Funktionen für FileName-Handling -------------------------------
// File: FNAMESTR.CPP

#include <bool.h>
#include <tstring>
#include <stdlib.h>
#include <fnamestr.h>

string get_drive (const string &str)
{
string drive (_MAX_DRIVE, default_size);

	if ('\\' != str[0] || '\\' != str[1])	// UNC's beachten
		_splitpath (str.c_str(), (char *)drive.c_str(), NULL, NULL, NULL);

	drive.adjustlen();

return drive;
}

string get_path (const string &str)
{
string path (_MAX_PATH, default_size);

	_splitpath (str.c_str(), NULL, (char *)path.c_str(), NULL, NULL);
	path.adjustlen();

return path;
}

string get_name (const string &str)
{
string name (_MAX_FNAME, default_size);

	_splitpath (str.c_str(), NULL, NULL, (char *)name.c_str(), NULL);
	name.adjustlen();

return name;
}

string get_ext (const string &str)
{
string ext (_MAX_EXT, default_size);

	_splitpath (str.c_str(), NULL, NULL, NULL, (char *)ext.c_str());
	ext.adjustlen();

return ext;
}

