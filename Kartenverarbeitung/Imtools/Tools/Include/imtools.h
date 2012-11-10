/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/include/RCS/imtools.h,v 1.10 1995/06/30 22:22:01 bduggan Exp $
 **	Copyright (c) 1989-1995  San Diego Supercomputer Center (SDSC)
 **		a division of General Atomics, San Diego, California, USA
 **
 **	Users and possessors of this source code are hereby granted a
 **	nonexclusive, royalty-free copyright and design patent license to
 **	use this code in individual software.  License is not granted for
 **	commercial resale, in whole or in part, without prior written
 **	permission from SDSC.  This source is provided "AS IS" without express
 **	or implied warranty of any kind.
 **
 **	For further information contact:
 **		E-Mail:		info@sds.sdsc.edu
 **
 **		Surface Mail:	Information Center
 **				San Diego Supercomputer Center
 **				P.O. Box 85608
 **				San Diego, CA  92138-5608
 **				(619) 534-5000
 **/

/**
 **  FILE
 **	imtools.h	-  general include file for all image tools
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imtools.h contains generic macros and extern declarations for
 **	variables and functions used by most of the image tools.
 **
 **  PUBLIC CONTENTS
 **			d =defined constant
 **			f =function
 **			m =defined macro
 **			t =typedef/struct/union
 **			v =variable
 **			? =other
 **
 **	IMTOOLS...	d  tool version
 **	ImTools*	v  extern global declarations
 **	ImTools*	f  extern function declarations
 **
 **  PRIVATE CONTENTS
 **	none
 **
 **  HISTORY
 **	$Log: imtools.h,v $
 **	Revision 1.10  1995/06/30  22:22:01  bduggan
 **	removed strings.h
 **
 **	Revision 1.9  1995/06/29  00:39:58  bduggan
 **	updated copyright
 **
 **	Revision 1.8  1995/06/16  06:33:27  bduggan
 **	removed buildflagstable prototype
 **
 **	Revision 1.7  1995/06/16  06:24:37  bduggan
 **	Added three read options (for pagewidth, pageheight, dpi)
 **
 **	Revision 1.6  1995/05/18  00:06:25  bduggan
 **	Changed number of read,write options.
 **
 **	Revision 1.5  1995/02/07  21:58:14  bduggan
 **	Added prototypes for ImToolsAddReadWriteFlags,
 **	ImToolsMakeStandardFlagsTable, GetNameAndFormat,
 **	MergeOptions, and MergeEquivs
 **
 **	Revision 1.4  94/10/03  15:57:41  nadeau
 **	Updated to ANSI C and C++ compatibility by adding function prototypes.
 **	Changed all float arguments to double.
 **	Updated version number to 3.0.0.
 **	Updated copyright message.
 **	
 **	Revision 1.3  92/10/12  16:12:08  vle
 **	Added declarations for ImInfo.
 **	
 **	Revision 1.2  92/09/02  13:50:53  vle
 **	Updated copyright notice and version number to 2.1.
 **	
 **	Revision 1.1  91/10/22  14:05:43  nadeau
 **	Initial revision
 **	
 **/

#ifndef __IMTOOLS_H__


#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
//#include <sys/file.h>
#include <stdlib.h>
#include <string.h>
#include "sdsc.h"
#include "im.h"

#ifndef NULL
#define NULL
#endif

#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif


#include "imVersion.h"


/*
 *  GLOBALS
 *	ImTools*		-  extern global declarations
 *
 *  DESCRIPTION
 *	ImToolsProgram holds the argv[0] name of the program and is used
 *	in various error messages.
 *
 *	ImToolsVerbose flags whether we should print out verbose messages
 *	about what we are doing, or not.
 *
 *	ImToolsBaseHelp is the generic basic help string used by most of
 *	the image tools to describe the basic options.
 *
 *	ImToolsRegister and ImToolsFeedback are the user registration and
 *	feedback forms used by the image tools.
 *
 *	ImToolsBaseOptions and ImToolsBaseEquivs are the generic basic
 *	command-line options and equivalent option keywords used by most
 *	of the image tools.
 *
 */

IMTOOLS_API extern char   *ImToolsProgram;
IMTOOLS_API extern int ImToolsVerbose;

IMTOOLS_API extern char   *ImToolsBaseHelp;

IMTOOLS_API extern char   *ImToolsRegister;
IMTOOLS_API extern char   *ImToolsFeedback;

IMTOOLS_API extern char   *ImToolsInHelp;
IMTOOLS_API extern char   *ImToolsOutHelp;

#define IMTOOLSNWRITEOPTIONS	20
#define IMTOOLSNWRITEEQUIVS	0
IMTOOLS_API extern ArgOption ImToolsWriteOptions[];
IMTOOLS_API extern ArgEquiv  ImToolsWriteEquivs[];

#define IMTOOLSNREADOPTIONS	6 
#define IMTOOLSNREADEQUIVS	0
IMTOOLS_API extern ArgOption ImToolsReadOptions[];
IMTOOLS_API extern ArgEquiv  ImToolsReadEquivs[];

#if defined(_USE_MMFS_FOR_VFB_OPTIONAL)
#define IMTOOLSNOTHEROPTIONS	2
#else
#define IMTOOLSNOTHEROPTIONS	1
#endif // defined(_USE_MMFS_FOR_VFB_OPTIONAL)

#define IMTOOLSNOTHEREQUIVS	0
IMTOOLS_API extern ArgOption ImToolsOtherOptions[];
IMTOOLS_API extern ArgEquiv  ImToolsOtherEquivs[];






/*
 *  FUNCTIONS
 *	ImTools*		-  extern function declarations
 */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __STDC__
IMTOOLS_API extern int	 ImToolsMergeOptions( char* prefix, int nOpts1, ArgOption *opt1, int nOpts2,
			ArgOption *opt2, ArgOption **newopt );

IMTOOLS_API extern int	 ImToolsMergeEquivs( char* prefix, int nEquiv1, ArgEquiv *equiv1, int nEquiv2,
			ArgEquiv *equiv2, ArgEquiv **newequiv );
IMTOOLS_API extern int	 ImToolsIsFormat( char *name );
IMTOOLS_API extern TagTable *ImToolsMakeStandardFlagsTable (void);
IMTOOLS_API extern int	 ImToolsGetNameAndFormat(  char* flagName, int index, char* retName, char* retFormat);
IMTOOLS_API extern int       ImToolsAddReadWriteFlags (TagTable*, char* prefix );
IMTOOLS_API extern void	 ImToolsChangeTagEntry( TagTable *, char *tag, void *newvalue );
IMTOOLS_API extern int	 ImToolsErrorHandler( int severity, int imerrno,
			char *message );
IMTOOLS_API extern int	 ImToolsInfoHandler( char *program, char *filename,
			char *message );
IMTOOLS_API extern FILE	*ImToolsOpen( char *fileName, char *flags, char *format,
			char *actualFileName, char *actualFormat );
IMTOOLS_API extern void	 ImToolsFileRead( char *filename, char *format,
			TagTable *flags, TagTable *data );
IMTOOLS_API extern void	 ImToolsFileWrite( char *filename, char *format,
			TagTable *flags, TagTable *data );
IMTOOLS_API extern char*	ImToolsMergeHelp(char* first, char* second);

IMTOOLS_API extern int ImToolsUseMMFiles();
IMTOOLS_API extern int ImToolsSetUseMMFiles(int);

#else

extern int	 ImToolsMergeOptions( );
extern int	 ImToolsMergeEquivs( );
extern int	 ImToolsIsFormat( );
extern TagTable *ImToolsMakeStandardFlagsTable ();
extern int       ImToolsAddReadWriteFlags ();
extern int	 ImToolsGetNameAndFormat(  );
extern void	 ImToolsChangeTagEntry( );
extern int	 ImToolsErrorHandler( );
extern int	 ImToolsInfoHandler( );
extern FILE	*ImToolsOpen( );
extern void	 ImToolsFileRead( );
extern void	 ImToolsFileWrite( );
extern char*	ImToolsMergeHelp();

#endif

#ifdef __cplusplus
}
#endif

#endif /* __IMTOOLS_H__ */
