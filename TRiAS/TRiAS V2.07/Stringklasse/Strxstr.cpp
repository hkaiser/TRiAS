// strxstr -- operatr>>(istream &, string &)
#include <bool.h>
#include <ctype.h>
#include <limits.h>
#include <istream.h>
#include <ostream.h>
#include <streamb.h>

#include <string.h>
#include <tstring.hpp>

// extract into a string
istream &operator>> (istream &is, string &str)
{
_Bool changed = 0;

	str.remove();
	_TRY_BEGIN
	if (is.ipfx()) {
	// extract arbitrary characters
	int n = 0 < is.width() ? is.width() : INT_MAX;
	
		for (int ch; 0 < --n && str.length() < NPOS - 1
			     && (ch = is.rdbuf()->sbumpc()) != EOF; )
		{
			if (isspace(ch)) {	// put back white space and quit
				is.rdbuf() -> sputbackc(ch);
				break;
			}
			else
				str.append ((char)ch), changed = 1;
		}
	}
	if (!changed) is.clear (is.rdstate() | ios::failbit);
	is.width(0);
	is.isfx();
	
	_CATCH_ALL is.clear(is.rdstate() | ios::badbit); _RERAISE; _CATCH_END;
	
return (is);
}
