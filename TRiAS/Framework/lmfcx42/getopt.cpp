#include "StdAfx.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: getopt.cpp 1.2 1996/08/20 19:10:12 andy Exp andy $";
/* $Log: getopt.cpp $
// Revision 1.2  1996/08/20  19:10:12  andy
// initial version
//
// Revision 1.1  1996/07/12  17:16:15  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

// AFX_EXT_DATA	LPCTSTR optarg;
// AFX_EXT_DATA	int		optind = 1;
// AFX_EXT_DATA	int		opterr = 1;

AFX_EXT_API	int getopt(int argc, LPCTSTR *argv, LPCTSTR optstring, int& optind, LPCTSTR& optarg )
{
	LPCTSTR opt;
	static int inopt = 0;
//	static int optind = 1;

	if(optind >= argc || *argv[optind] != '-' && inopt == 0)
		return(EOF);
	opt = argv[optind] + 1 + inopt;
	if(*opt == '-') {
		optind++;
		return(EOF);
	}
	if(*opt == '\0')
		opt = " ";
	while(*optstring++ != *opt)
		if(*optstring == '\0') {
			optind++;
			return('?');
		}
	if(*optstring == ':') {
		inopt = 0;
		optind++;
		if(opt[1] != '\0')
			optarg = &opt[1];
		else
			optarg = argv[optind++];
	} else
		if(opt[1] != '\0')
			inopt++;
		else {
			inopt = 0;
			optind++;
		}
	return(*opt);
}
