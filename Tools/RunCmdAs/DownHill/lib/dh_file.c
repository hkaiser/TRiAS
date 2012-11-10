/*****************************************************************************
 *                                                                           *
 * DH_FILE.C                                                                 *
 *                                                                           *
 * Freely redistributable and modifiable.  Use at your own risk.             *
 *                                                                           *
 * Copyright 1994 The Downhill Project                                       *
 *                                                                           *
 *****************************************************************************/

#if !defined(lint) && !defined(_NOIDENT)
static const char* rcsid = "@(#)$RCSfile: dh_file.c,v $ $Revision: 1.1.2.1 $ (DOWNHILL) $Date: 1997/04/17 06:17:21 $";
#endif


/* Include stuff *************************************************************/
#include "INCLUDE/DH.H"
#include <utime.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/param.h>
#include <strings.h>

/* Function stuff ************************************************************/

/* Read info about a link ================================================== */
#if (_DOWNHILL_POSIX_SOURCE == 0)
int readlink(char* file_Name,char* buf_Mem,int buf_Size)
{
	/* See if the file exists */
	if (access(file_Name,X_OK) == -1)
	{
		errno = ENOENT;
	}
	else
	{
		errno = EINVAL;
	}

	/* Either way, it's not a link */	
	return -1;
}
#endif

/* Set the time of a file ================================================== */
#if (_DOWNHILL_POSIX_SOURCE == 0)
int utimes(char* file_Name,struct timeval file_Time[])
{
	struct _utimbuf file_Utime;

	/* Fill out the structure */
	file_Utime.actime = file_Time[0].tv_sec;
	file_Utime.modtime = file_Time[1].tv_sec;

	/* And call utime() */
	return _utime(file_Name,&file_Utime);
}
#endif

/* Change the ownership of a file ========================================== */
int chown(char* file_Name,uid_t file_User,gid_t file_Group)
{
	/* Pretend we did something */
	return 0;
}

/* Change the ownership of a file descriptor =============================== */
#if (_DOWNHILL_POSIX_SOURCE == 0)
int fchown(int file_Fd,uid_t file_User,gid_t file_Group)
{
	/* Pretend we did something */
	return 0;
}
#endif

/* Create a Downhill_File_Stat structure from a _stat structure ============ */
static void downhill_Stat_Create(struct Downhill_File_Stat* file_Info,
             struct _stat* file_InfoReal)
{
	file_Info->st_dev = file_InfoReal->st_dev;
	file_Info->st_ino = file_InfoReal->st_ino;
	file_Info->st_mode = file_InfoReal->st_mode;
	file_Info->st_nlink = file_InfoReal->st_nlink;
	file_Info->st_uid = Downhill_User_IdReal;
	file_Info->st_gid = Downhill_Group_IdReal;
	file_Info->st_rdev = file_InfoReal->st_rdev;
	file_Info->st_size = file_InfoReal->st_size;
	file_Info->st_atime = file_InfoReal->st_atime;
	file_Info->st_mtime = file_InfoReal->st_mtime;
	file_Info->st_ctime = file_InfoReal->st_ctime;
#if (_DOWNHILL_POSIX_SOURCE == 0)
	file_Info->st_blksize = _DOWNHILL_STAT_BLOCKSIZE;
#endif
}

/* Stat a file ============================================================= */
int Downhill_File_Stat(const char                *file_Name,
		       struct Downhill_File_Stat *file_Info)
{
	struct _stat file_InfoReal;

	/* Get the stat information */
	if (_stat(file_Name,&file_InfoReal) != 0)
	{
		return -1;
	}

	/* Fill in the structure */
	downhill_Stat_Create(file_Info,&file_InfoReal);

	return 0;
}

/* Stat a file descriptor ================================================== */
int Downhill_File_StatFd(int file_Fd,struct Downhill_File_Stat* file_Info)
{
	struct _stat file_InfoReal;

	/* Get the fstat information */
	if (_fstat(file_Fd,&file_InfoReal) != 0)
	{
		return -1;
	}

	/* Fill in the structure */
	downhill_Stat_Create(file_Info,&file_InfoReal);

	return 0;
}

/* Stat a file or a symlink ================================================ */
#if (_DOWNHILL_POSIX_SOURCE == 0)
int lstat(const char *file_Path, struct stat* file_Stat)
{
	/* It can't be a link, so just stat file */
	return stat(file_Path,file_Stat);
}
#endif

/* Set the host file status ================================================ */
#if (_DOWNHILL_POSIX_SOURCE == 0)
int sethostent(int host_Stayopen)
{
	return 0;
}
#endif

/* Close the host file ===================================================== */
#if (_DOWNHILL_POSIX_SOURCE == 0)
int endhostent(void)
{
	return 0;
}
#endif

/* Truncate an open file =================================================== */
#if (_DOWNHILL_POSIX_SOURCE == 0)
int ftruncate(int file_Fd,off_t file_Size)
{
	return _chsize(file_Fd,file_Size);
}
#endif

/* Truncate a file ========================================================= */
#if (_DOWNHILL_POSIX_SOURCE == 0)
int truncate(char* file_Name,off_t file_Size)
{
	int file_Fd;
	int truncate_Result;

	file_Fd = open(file_Name,O_WRONLY);
	if (file_Fd == -1)
	{
		return -1;
	}
	truncate_Result = ftruncate(file_Fd,file_Size);
	close(file_Fd);

	return truncate_Result;
}
#endif

/* Get current working directory =========================================== */
char* Downhill_Get_CWD(char* buffer, int len)
{
    char* result = _getcwd(buffer, len);
    if (result)
    {
	Downhill_DOS_to_UNIX(result);
    }
    return result;
}

/* Rename a file =========================================================== */
#undef rename
int Downhill_File_Rename(const char* from, const char* to)
{
    /*
     * This routine is necessary because on Win32 rename does
     * not succeed if the destination file already exists whereas
     * on UNIX such a destination file is silently unlinked.
     *
     * This implementation carefully unlinks the destination file
     * in such a way as to minimise the chances of the destination
     * file being inadvertently lost.
     *
     * The only way this can occur is if the destination file
     * has been renamed to a temporary file, the actual rename
     * fails and then the temporary file cannot be renamed back
     * to the name of the destination file.
     */
    char prefix[10];
    const char* temp = NULL;

    /* Success on renaming a file to itself */
    if (strcasecmp(from, to) == 0) {
	return 0;
    }
    
    /*
     * This is where we change the DOS semantics to UNIX
     * semantics. Under DOS, if the destination exists
     * then the rename always fails, regardless of whether
     * the caller has permission to delete the destination file.
     * Under UNIX a rename will succeed if the caller is
     * allowed to delete the destination file.
     */
    if (access(to, F_OK) == 0) {
	/*
	 * First rename destination to a temporary file in the same
	 * directory as the destination. This ensures that we are
	 * not renaming across a filesystem which may happen if
	 * we just use TMPDIR.
	 */
	char  tempdir[MAXPATHLEN];
	char* slash;
	strcpy(tempdir, to);
	for(slash = tempdir + strlen(tempdir) - 1; slash >= tempdir; --slash) {
	    if (*slash == '/' || *slash == '\\') {
		*slash = '\0';
		break;
	    }
	}
	
	sprintf(prefix, "dhfr%d", getpid());
	temp = _tempnam(tempdir, prefix);
	if (temp == NULL) {
	    return -1;
	}

	if (rename(to, temp) == -1 && errno != ENOENT) {
	    return -1;
	}
	
	/* We now have a temporary file - we need to make sure we remove it */
    }

    /* Now rename the source to the destination and unlink the temporary */
    if (rename(from, to) == -1) {
	int saved = errno;
	if (temp) {
	    (void)rename(temp, to);
	    (void)_unlink(temp);
	}
	errno = saved;
	return -1;
    }
    if (temp) {
	(void)_unlink(temp);
    }
    
    /* Success */
    return 0;
}

void
Downhill_DOS_to_UNIX(char *path)
{
  for(; *path; path++)
    if (*path == _DOWNHILL_OTHER_SLASH)
      *path = _DOWNHILL_SLASH;
}

void
Downhill_UNIX_to_DOS(char *path)
{
  for(; *path; path++)
    if (*path == _DOWNHILL_SLASH)
      *path = _DOWNHILL_OTHER_SLASH;
}
