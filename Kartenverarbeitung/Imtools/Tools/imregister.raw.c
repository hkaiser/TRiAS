/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imregister.raw.c,v 1.4 1995/06/29 00:40:07 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imregister.raw.c,v 1.4 1995/06/29 00:40:07 bduggan Exp $"

/**
 **  FILE
 **	imregister.c	-  Initialize the ImToolsRegister string
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imregister.c initializes the standard Image Tools registration form
 **	global character string.
 **
 **  PUBLIC CONTENTS
 **			d =defined constant
 **			f =function
 **			m =defined macro
 **			t =typedef/struct/union
 **			v =variable
 **			? =other
 **
 **	ImToolsRegister	v  Image Tools registration form
 **
 **  PRIVATE CONTENTS
 **	none
 **
 **  HISTORY
 **	$Log: imregister.raw.c,v $
 **	Revision 1.4  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.4  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.3  1994/10/03  15:49:52  nadeau
 **	Updated to ANSI C and C++ compatibility.
 **	Updated comments.
 **	Updated copyright message.
 **
 **	Revision 1.2  92/08/31  17:13:24  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.1  91/10/03  13:20:02  nadeau
 **	Initial revision
 **	
 **/

#include "imtools.h"

char *ImToolsRegister = "\
