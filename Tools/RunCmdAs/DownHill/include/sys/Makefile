#
# HISTORY
# 	Add uio calls: readv, writev.
# 	Make libdownhill installable.
# 	Put include guards around stdlib.h.
# 	[1997/05/21  07:35:51  tbartley]

DATAFILES	= dir.h		\
		  dirent.h	\
		  errno.h	\
		  fcntl.h	\
		  file.h	\
		  param.h	\
		  resource.h	\
		  signal.h	\
		  socket.h	\
		  stat.h	\
		  time.h	\
		  types.h	\
		  uio.h		\
		  unistd.h	\
		  utsname.h	\
		  wait.h

INCLUDES	= ${DATAFILES}

EXPDIR		= /usr/include/sys/

ILIST		= ${INCLUDES}
IDIR		= /include/sys/

.include <${RULES_MK}>
