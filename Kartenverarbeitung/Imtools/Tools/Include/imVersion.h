/*
 *  CONSTANTS
 *	IMTOOLS...		-  tool version
 *
 *  DESCRIPTION
 *	This is the current version number for the tools.  Note that all
 *	tools use this same version number, and thus track release versions
 *	together.
 */
#define IMTOOLSMAJOR	3
#define IMTOOLSMINOR	1	// #HK000327
#define IMTOOLSSUBMINOR	8

#if defined(WIN32)
#define IMTOOLSBUILDDATE	"021015"
#define IMTOOLSCOPYRIGHT	\
	"Copyright (c) 1989-1995 San Diego Supercomputer Center (SDSC), CA, USA" \
	"\nCopyright (c) 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam" \
	"\n(port to Win32 platforms), #HK" IMTOOLSBUILDDATE
#else
#define IMTOOLSCOPYRIGHT	\
	"Copyright (c) 1989-1995  San Diego Supercomputer Center (SDSC), CA, USA" 
#endif // defined(WIN32)

