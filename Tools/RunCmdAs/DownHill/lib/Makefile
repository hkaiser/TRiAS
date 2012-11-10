#
# HISTORY
# 	Add uio calls: readv, writev.
# 	Make libdownhill installable.
# 	Put include guards around stdlib.h.
# 	[1997/05/21  07:35:57  tbartley]

LIBRARIES	= libdownhill.a

EXPLIB_TARGETS	= export_libdownhill.a
EXPDIR		= /usr/lib/

OFILES		= dh_dir.o dh_env.o dh_file.o dh_grp.o dh_mem.o dh_misc.o \
		  dh_net.o dh_opt.o dh_pipe.o dh_proc.o dh_sig.o dh_str.o \
		  dh_time.o dh_uio.o dh_usr.o

ILIST		= ${LIBRARIES}
IDIR		= /lib/

.include <${RULES_MK}>

# *****************************************************************************
# *                                                                           *
# * MAKEFILE                                                                  *
# *                                                                           *
# * Freely redistributable and modifiable.  Use at your own risk.             *
# *                                                                           *
# * Copyright 1994 The Downhill Project                                       *
# *                                                                           *
# *****************************************************************************

# How things are compiled =====================================================
CMP_SYSV            = YES                  # Compile as System V-compliant?

# How things work =============================================================
#
# Many of the values here are either not important or impossible to configure
# at compile time and hence there is not much point configuring them.
#
# The ones that are relevant to us are:
#
#	DWN_MACHINE_TYPE
# and 	DWN_GETOPT_SWITCH
#
# The others are left with their default configuration values.
#
DWN_MACHINE_TYPE      = x86
DWN_GETOPT_SWITCH     = -
DWN_HOSTSEQUIV_PATH   = C:/etc/hosts.eqv
DWN_RHOSTS_FILE       = rhosts
DWN_NETRC_FILE        = netrc
DWN_STAT_BLOCKSIZE    = 512
DWN_USER_NAME         = user
DWN_USER_IDREAL       = 0
DWN_USER_IDEFFECTIVE  = 0
DWN_USER_IDSAVED      = 0
DWN_USER_PASSWORD     = *
DWN_USER_GECOS        = User
DWN_USER_DIR          = C:/
DWN_USER_SHELL        = C:/command.com
DWN_GROUP_NAME        = group
DWN_GROUP_IDREAL      = 0
DWN_GROUP_IDEFFECTIVE = 0
DWN_GROUP_IDSAVED     = 0
DWN_GROUP_PASSWORD    = *

.if ${CMP_SYSV} == YES
DHDEFS		+= -D_DOWNHILL_UNIX_SYSV
.endif
.if ${DWN_MACHINE_TYPE} != ""
DHDEFS		+= -D_DOWNHILL_MACHINE_TYPE="\"${DWN_MACHINE_TYPE}\""
.endif
.if ${DWN_GETOPT_SWITCH} != ""
DHDEFS		+= -D_DOWNHILL_GETOPT_SWITCH="'${DWN_GETOPT_SWITCH}'"
.endif
.if ${DWN_STAT_BLOCKSIZE} != ""
DHDEFS		+= -D_DOWNHILL_STAT_BLOCKSIZE=${DWN_STAT_BLOCKSIZE}
.endif
.if ${DWN_HOSTSEQUIV_PATH} != ""
DHDEFS		+= -D_DOWNHILL_HOSTSEQUIV_PATH="\"${DWN_HOSTSEQUIV_PATH}\""
.endif
.if ${DWN_RHOSTS_FILE} != ""
DHDEFS		+= -D_DOWNHILL_RHOSTS_FILE="\"${DWN_RHOSTS_FILE}\""
.endif
.if ${DWN_NETRC_FILE} != ""
DHDEFS		+= -D_DOWNHILL_NETRC_FILE="\"${DWN_NETRC_FILE}\""
.endif
.if ${DWN_USER_NAME} != ""
DHDEFS		+= -D_DOWNHILL_USER_NAME="\"${DWN_USER_NAME}\""
.endif
.if ${DWN_USER_IDREAL} != ""
DHDEFS		+= -D_DOWNHILL_USER_IDREAL=${DWN_USER_IDREAL}
.endif
.if ${DWN_USER_IDEFFECTIVE} != ""
DHDEFS		+= -D_DOWNHILL_USER_IDEFFECTIVE=${DWN_USER_IDEFFECTIVE}
.endif
.if ${DWN_USER_IDSAVED} != ""
DHDEFS		+= -D_DOWNHILL_USER_IDSAVED=${DWN_USER_IDSAVED}
.endif
.if ${DWN_USER_PASSWORD} != ""
DHDEFS		+= -D_DOWNHILL_USER_PASSWORD="\"${DWN_USER_PASSWORD}\""
.endif
.if ${DWN_USER_DIR} != ""
DHDEFS		+= -D_DOWNHILL_USER_DIR="\"${DWN_USER_DIR}\""
.endif
.if ${DWN_USER_GECOS} != ""
DHDEFS		+= -D_DOWNHILL_USER_GECOS="\"${DWN_USER_GECOS}\""
.endif
.if ${DWN_USER_SHELL} != ""
DHDEFS		+= -D_DOWNHILL_USER_SHELL="\"${DWN_USER_SHELL}\""
.endif
.if ${DWN_GROUP_NAME} != ""
DHDEFS		+= -D_DOWNHILL_GROUP_NAME="\"${DWN_GROUP_NAME}\""
.endif
.if ${DWN_GROUP_IDREAL} != ""
DHDEFS		+= -D_DOWNHILL_GROUP_IDREAL=${DWN_GROUP_IDREAL}
.endif
.if ${DWN_GROUP_IDEFFECTIVE} != ""
DHDEFS		+= -D_DOWNHILL_GROUP_IDEFFECTIVE=${DWN_GROUP_IDEFFECTIVE}
.endif
.if ${DWN_GROUP_IDSAVED} != ""
DHDEFS		+= -D_DOWNHILL_GROUP_IDSAVED=${DWN_GROUP_IDSAVED}
.endif
.if ${DWN_GROUP_PASSWORD} != ""
DHDEFS		+= -D_DOWNHILL_GROUP_PASSWORD="\"${DWN_GROUP_PASSWORD}\""
.endif

DHINCLUDES	= -Iinclude

DHFLAGS		= ${DHINCLUDES} ${DHDEFS}

dh_dir.o_CFLAGS		= ${DHFLAGS} ${CFLAGS}
dh_env.o_CFLAGS		= ${DHFLAGS} ${CFLAGS}
dh_file.o_CFLAGS	= ${DHFLAGS} ${CFLAGS}
dh_grp.o_CFLAGS		= ${DHFLAGS} ${CFLAGS}
dh_mem.o_CFLAGS		= ${DHFLAGS} ${CFLAGS}
dh_misc.o_CFLAGS	= ${DHFLAGS} ${CFLAGS}
dh_net.o_CFLAGS		= ${DHFLAGS} ${CFLAGS}
dh_opt.o_CFLAGS		= ${DHFLAGS} ${CFLAGS}
dh_pipe.o_CFLAGS	= ${DHFLAGS} ${CFLAGS}
dh_proc.o_CFLAGS	= ${DHFLAGS} ${CFLAGS}
dh_sig.o_CFLAGS		= ${DHFLAGS} ${CFLAGS}
dh_str.o_CFLAGS		= ${DHFLAGS} ${CFLAGS}
dh_time.o_CFLAGS	= ${DHFLAGS} ${CFLAGS}
dh_usr.o_CFLAGS		= ${DHFLAGS} ${CFLAGS}
