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
\n\
This form has been automatically generated by use of the '-register' option on\n\
a tool written and distributed by the San Diego Supercomputer Center (SDSC).\n\
We provide this form so that users of our software can register themselves to\n\
receive announcements of new tool releases.  User registration also lets us\n\
know who is using our tools and what they are using them for.  Such information\n\
helps us tailor our development efforts to best meet user needs.\n\
\n\
Filling out this registration form in no way commits you or us to anything.\n\
\n\
After you have filled out the questionnaire that follows, please send this to:\n\
\n\
	E-mail:		info@sdsc.edu\n\
\n\
	Surface mail:	Software Products Information\n\
			San Diego Supercomputer Center\n\
			P.O. Box 85608\n\
			San Diego, CA  92186-9784\n\
\n\
	FAX:		(619) 534-5113\n\
\n\
If you have questions about this form, or any of our software products, please\n\
feel free to mail to any of the above or call us at:\n\
\n\
			(619) 534-5100  8am-5pm, Pacific time\n\
\n\
-------------------------------------------------------------------------------\n\
				User Registration!\n\
\n\
Who are you?\n\
	Name:		\n\
	Organization:	\n\
	Group:		\n\
	Job Title:	\n\
	Phone number:	\n\
	FAX number:	\n\
	E-Mail address:	\n\
	Surface mail address:\n\
\n\
What do you do?\n\
	Primary company function:\n\
	Your function:\n\
\n\
What equipment do you have?\n\
	Machine Name		Model		OS / Version	How Many?\n\
	----------------------- --------------- --------------- ---------------\n\
\n\
What software do you have?\n\
	Animation and Rendering\n\
		[ ] Alias\n\
		[ ] RenderMan\n\
		[ ] SDSC Synu\n\
		[ ] SoftImage\n\
		[ ] Wavefront TAV\n\
		[ ] Other:  \n\
	Visualization:\n\
		[ ] AVS\n\
		[ ] Khoros\n\
		[ ] Silicon Graphics Explorer\n\
		[ ] IBM Data Explorer\n\
		[ ] Wavefront Data Visualizer\n\
		[ ] Other:  \n\
	Image handling:\n\
		[ ] Debabelizer\n\
		[ ] ImageMagick\n\
		[ ] PBM or PBM+\n\
		[ ] Photoshop\n\
		[ ] SDSC Image Tools\n\
		[ ] Utah Raster Toolkit (RLE)\n\
		[ ] Other:  \n\
	Windowing:\n\
		[ ] NeXTstep\n\
		[ ] SunView\n\
		[ ] Sun NeWS\n\
		[ ] X Window System\n\
			[ ] Motif\n\
			[ ] XView (Sun OpenLook)\n\
		[ ] Other:  \n\
\n"
"How did you hear about our products?\n\
	[ ] A colleague told you\n\
	[ ] UNIX net news announcement\n\
	[ ] SDSC Gather/Scatter newsletter\n\
	[ ] SDSC announcements mailing list\n\
	[ ] Found it installed on your system\n\
	[ ] Don't remember\n\
	[ ] Other:  \n\
\n\
Thanks!\n\
";
