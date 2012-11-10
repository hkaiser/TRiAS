# HISTORY
# 	Add uio calls: readv, writev.
# 	Make libdownhill installable.
# 	Put include guards around stdlib.h.
# 	[1997/05/21  07:35:40  tbartley]

EXPINC_SUBDIRS	= downhill netinet sys
SUBDIRS		= downhill netinet sys

DATAFILES	= ar.h		\
		  dirent.h	\
		  downhill.h	\
		  errno.h	\
		  fcntl.h	\
		  getopt.h	\
		  grp.h		\
		  malloc.h	\
		  netdb.h	\
		  pwd.h		\
		  ranlib.h	\
		  signal.h	\
		  stdio.h	\
		  stdlib.h	\
		  string.h	\
		  strings.h	\
		  unistd.h	\
		  utime.h

INCLUDES	= ${DATAFILES}

EXPDIR		= /usr/include/
ILIST		= ${INCLUDES}
IDIR		= /include/

.include <${RULES_MK}>
