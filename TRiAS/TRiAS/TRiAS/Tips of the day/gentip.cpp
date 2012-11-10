
#include <stl.h>
#include <ospace\string.h>
#include <iostream.h>

char s_cbBuffer[1025];

void main (int argc, char *argv[])
{
	if (argc != 1) throw "Usage: GenTip\n";
	
vector<os_string> v;

	while (!cin.eof()) {
		cin.getline (s_cbBuffer, sizeof(s_cbBuffer), '\n');

	os_string str = s_cbBuffer;

		str += '\n';
		v.push_back (str);
	}
	random_shuffle (v.begin(), v.end());
	copy (v.begin(), v.end(), ostream_iterator<os_string>(cout));
}
