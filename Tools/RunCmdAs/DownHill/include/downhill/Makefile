#
# HISTORY
# 	Add uio calls: readv, writev.
# 	Make libdownhill installable.
# 	Put include guards around stdlib.h.
# 	[1997/05/21  07:35:43  tbartley]

DATAFILES	= dh_inc.h	\
		  dh_posix.h

INCLUDES	= ${DATAFILES}

EXPDIR		= /usr/include/downhill/

ILIST		= ${INCLUDES}
IDIR		= /include/downhill/

.include <${RULES_MK}>

dh_inc.h:	always
	echo "#define _DOWNHILL_INCLUDE_DIR <${VCDir}/include" > dh_inc.h
dh_posix.h:	always
	echo "#define _DOWNHILL_POSIX_SOURCE 0" > dh_posix.h

always:
