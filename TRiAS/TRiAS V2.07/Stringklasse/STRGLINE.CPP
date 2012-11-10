// strgline -- getline(istream &, string &, char)
#include <bool.h>
#include <iostream.h>
#include <tstring>

istream &getline (istream &is, string &str, char delim)
{	// get into string up through delimiter or count
size_t n = 0;
_Bool copied = 0;

	str.remove();
	_TRY_BEGIN
	if (is.ipfx(1))
		for (int ch; ; )
			if (NPOS - 1 <= n) {
			// record count failure and quit
				is.clear(is.rdstate() | ios::failbit);
				break;
			} else if ((ch = is.rdbuf() -> sbumpc()) == EOF) {
			// record eof and quit
				is.clear(is.rdstate() | ios::eofbit);
				break;
			} else {
				if (ch == delim)
					break;
				str.append ((char )ch), ++n, copied = 1;
			}

	if (!copied)
		is.clear(is.rdstate() | ios::failbit);
	is.isfx();

	_CATCH_ALL is.clear(is.rdstate() | ios::badbit); _RERAISE; _CATCH_END;

return is;
}

