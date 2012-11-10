/*****************************************************************************
 *                                                                           *
 * sys/unistd.h                                                              *
 *                                                                           *
 * Freely redistributable and modifiable.  Use at your own risk.             *
 *                                                                           *
 * Copyright 1994 The Downhill Project                                       *
 *                                                                           *
 *****************************************************************************/
/*
 * HISTORY
 * 	Allow selection of macro definitions only.
 * 	That is, provide a compatibility layer that requires no library
 * 	functions only macro definitions. This is enabled by defining the
 * 	macro DOWNHILL_NO_FUNCTIONS.
 * 	[1997/06/23  12:12:40  tbartley]
 *
 * 	Add definition for fsync as _commit.
 * 	[1997/05/26  07:41:31  tbartley]
 */

#if !defined(_DOWNHILL_SYS_UNISTD_H)
#define _DOWNHILL_SYS_UNISTD_H


/* Include stuff *************************************************************/
#include "DOWNHILL/DH_POSIX.H"
#include <stdio.h>
#include <sys/types.h>
#include <io.h>
#include <process.h>
#include <direct.h>

/* Define stuff **************************************************************/
#if defined(_MSC_VER) && !defined(_NTSDK)
#  define access	_access
#  define chdir		_chdir
#  define chsize	_chsize
#  define close		_close
#  define cwait		_cwait
#  define creat		_creat
#  define dup		_dup
#  define dup2		_dup2
#  define eof		_eof
#  define execl		_execl
#  define execle	_execle
#  define execlp	_execlp
#  define execlpe	_execlpe
#  define execv		_execv
#  define execve	_execve
#  define execvp	_execvp
#  define execvpe	_execvpe
#  define filelength	_filelength
#  define fsync		_commit
#  define getpid	_getpid
#  define isatty	_isatty
#  define locking	_locking
#  define lseek		_lseek
#  define open		_open
#  define read		_read
#  define rmdir		_rmdir
#  define setmode	_setmode
#  define sopen		_sopen
#  define spawnl	_spawnl
#  define spawnle	_spawnle
#  define spawnlp	_spawnlp
#  define spawnlpe	_spawnlpe
#  define spawnv	_spawnv
#  define spawnve	_spawnve
#  define spawnvp	_spawnvp
#  define spawnvpe	_spawnvpe
#  define tell		_tell
#  define umask		_umask
#  define unlink	_unlink
#  define write		_write
#endif

/* File premissions ======================================================== */
#define F_OK 0
#define X_OK 0
#define W_OK 2
#define R_OK 4

/* lseek() positions ======================================================= */
#if (_DOWNHILL_POSIX_SOURCE == 0)
#define L_SET  SEEK_SET
#define L_INCR SEEK_CUR
#define L_XTND SEEK_END
#endif


#ifndef	DOWNHILL_NO_FUNCTIONS

/* Extern stuff **************************************************************/
extern int   opterr;
extern int   optind;
extern int   optopt;
extern char* optarg;


/* Redefinition stuff ********************************************************/
#undef  getcwd
#define getcwd(file_Buffer, file_Length) \
	Downhill_Get_CWD(file_Buffer, file_Length)

/* Prototype stuff ***********************************************************/
uid_t        getuid(void);
uid_t        geteuid(void);
int          setuid(uid_t user_Id);
gid_t        getgid(void);
gid_t        getegid(void);
int          getgroups(int group_Max,gid_t group_Id[]);
int          setgid(gid_t group_Id);
unsigned int sleep(unsigned int sleep_Duration);
int          pause(void);
int          chown(char* file_Name,uid_t file_User,gid_t file_Group);
#if (_DOWNHILL_POSIX_SOURCE == 0)
int          setruid(uid_t user_Id);
int          seteuid(uid_t user_Id);
int          setrgid(gid_t group_Id);
int          setegid(gid_t group_Id);
int          fchown(int file_Fd,uid_t file_User,gid_t file_Group);
int          getopt(int arg_Count,char* arg_Value[],char flag_List[]);
int          readlink(char* file_Name,char* buf_Mem,int buf_Size);
int          ftruncate(int file_Fd,off_t file_Size);
int          truncate(char* file_Name,off_t file_Size);
char*	     Downhill_Get_CWD(char* file_Buffer, int file_Size);
int          pipe(int handle[2], int inherit[2], int bufferSize, int mode);
#endif

#endif	/* DOWNHILL_NO_FUNCTIONS */

#endif /* _DOWNHILL_SYS_UNISTD_H */
