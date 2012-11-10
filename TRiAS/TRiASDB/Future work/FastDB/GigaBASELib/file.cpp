//-< FILE.CPP >------------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// System dependent implementation of mapped on memory file
//-------------------------------------------------------------------*--------*

#define _LARGEFILE64_SOURCE 1 // access to files greater than 2Gb in Solaris

#include "gigabase.h"

dbFile::~dbFile() 
{
    close();
}

#ifdef _WIN32

class OS_info : public OSVERSIONINFO { 
  public: 
    OS_info() { 
	dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(this);
    }
};

static OS_info osinfo;

#define BAD_POS 0xFFFFFFFF // returned by SetFilePointer and GetFileSize


dbFile::dbFile()
{
    fh = INVALID_HANDLE_VALUE;
}

int dbFile::open(char const* fileName, int attr)
{
    fh = CreateFile(fileName, (attr & read_only) 
		    ? GENERIC_READ : GENERIC_READ|GENERIC_WRITE, 0, NULL,
		    (attr & read_only) ? OPEN_EXISTING 
		    : (attr & truncate) ? CREATE_ALWAYS : OPEN_ALWAYS,
		    FILE_FLAG_NO_BUFFERING | ((attr & sequential) 
		    ? FILE_FLAG_SEQUENTIAL_SCAN : FILE_FLAG_RANDOM_ACCESS),
		    NULL);
    if (fh == INVALID_HANDLE_VALUE) {
	return GetLastError();
    }
    return ok;
}

int dbFile::read(offs_t pos, void* buf, size_t size)
{  
    DWORD readBytes;
    if (osinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) { 
	OVERLAPPED Overlapped;
	Overlapped.Offset = nat8_low_part(pos);
	Overlapped.OffsetHigh = nat8_high_part(pos);
	Overlapped.hEvent = NULL;
	if (ReadFile(fh, buf, size, &readBytes, &Overlapped)) { 
            return readBytes == size ? ok : eof;
	} else { 
	    int rc = GetLastError();
	    return (rc == ERROR_HANDLE_EOF) ? eof : rc;
	}
    } else { 
	LONG high_pos = nat8_high_part(pos); 
	dbCriticalSection cs(mutex);
	if (SetFilePointer(fh, nat8_low_part(pos), 
			   &high_pos, FILE_BEGIN) != BAD_POS 
	    && ReadFile(fh, buf, size, &readBytes, NULL))
	{
            return (readBytes == size) ? ok : eof;
	} else { 
	    int rc = GetLastError();
	    return rc == ERROR_HANDLE_EOF ? eof : rc;
	} 
    }
}		    

int dbFile::read(void* buf, size_t size)
{  
    DWORD readBytes;
    if (ReadFile(fh, buf, size, &readBytes, NULL)) {
	return (readBytes == size) ? ok : eof;
    } else { 
	int rc = GetLastError();
	return rc == ERROR_HANDLE_EOF ? eof : rc;
    } 
}		    

int dbFile::write(void const* buf, size_t size)
{  
    DWORD writtenBytes;
    return !WriteFile(fh, buf, size, &writtenBytes, NULL)
	? GetLastError() : (writtenBytes == size) ? ok : eof;
}

int dbFile::write(offs_t pos, void const* buf, size_t size)
{  
    DWORD writtenBytes;
    if (osinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) { 
	OVERLAPPED Overlapped;
	Overlapped.Offset = nat8_low_part(pos);
	Overlapped.OffsetHigh = nat8_high_part(pos);
	Overlapped.hEvent = NULL;
	return WriteFile(fh, buf, size, &writtenBytes, &Overlapped)
	    ? writtenBytes == size ? ok : eof
	    : GetLastError();
    } else { 
	LONG high_pos = nat8_high_part(pos); 
	dbCriticalSection cs(mutex);
	return SetFilePointer(fh, nat8_low_part(pos), &high_pos, FILE_BEGIN)
	    == BAD_POS ||
	    !WriteFile(fh, buf, size, &writtenBytes, NULL)
	    ? GetLastError() 
	    : (writtenBytes == size) ? ok : eof;
    }
}		    


int dbFile::flush()
{
    return FlushFileBuffers(fh) ? ok : GetLastError();
}

int dbFile::close()
{
    if (fh != INVALID_HANDLE_VALUE) { 
	if (CloseHandle(fh)) { 
	    fh = INVALID_HANDLE_VALUE; 
	    return ok;
	} else { 
	    return GetLastError();
	}
    } else { 
	return ok;
    }
}

void* dbFile::allocateBuffer(size_t size) 
{
    return VirtualAlloc(NULL, size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
}

void  dbFile::deallocateBuffer(void* buffer)
{
    VirtualFree(buffer, 0, MEM_RELEASE);
}

size_t dbFile::ramSize()
{
    MEMORYSTATUS memStat;
    GlobalMemoryStatus(&memStat);
    return memStat.dwTotalPhys;
} 


char* dbFile::errorText(int code, char* buf, size_t bufSize)
{
    int len;

    switch (code) { 
      case ok:
	strncpy(buf, "No error", bufSize);
	break;
      case eof:
	strncpy(buf, "Transfer less bytes than specified", bufSize);
	break;
      default:
	len = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
			    NULL,
			    code,
			    0,
			    buf,
			    bufSize,
			    NULL);
	if (len == 0) { 
	    char errcode[64];
	    sprintf(errcode, "unknown error %u", code);
	    strncpy(buf, errcode, bufSize);
	}
    }
    return buf;
}

#else // Unix

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#ifdef __linux__
extern "C" int8 llseek(int fd, int8 offs, unsigned int whence);
#define lseek(fd, offs, whence) llseek(fd, offs, whence)
#endif

dbFile::dbFile()
{
    fd = -1;
}

int dbFile::open(char const* name, int attr) 
{
#if defined(__svr4__)
    fd = ::open64(name, ((attr & read_only) ? O_RDONLY : O_CREAT|O_RDWR)
		  | ((attr & truncate) ? O_TRUNC : 0), 0666);
#else
    fd = ::open(name, ((attr & read_only) ? O_RDONLY : O_CREAT|O_RDWR)
		| ((attr & truncate) ? O_TRUNC : 0), 0666);
#endif
    if (fd < 0) { 
	return errno;
    }
    return ok;
}

int dbFile::read(offs_t pos, void* buf, size_t size)
{  
    ssize_t rc;
#if defined(__svr4__)
    rc = pread64(fd, buf, size, pos);
#else
    { 
	dbCriticalSection cs(mutex);
	if (offs_t(lseek(fd, pos, SEEK_SET)) != pos) { 
	    return errno;
	}
	rc = ::read(fd, buf, size);
    }
#endif
    if (rc == -1) { 
	return errno;
    } else if (size_t(rc) != size) { 
	return eof;
    } else { 
	return ok;
    }
}

int dbFile::read(void* buf, size_t size)
{
    ssize_t rc = ::read(fd, buf, size);
    if (rc == -1) { 
	return errno;
    } else if (size_t(rc) != size) { 
	return eof;
    } else { 
	return ok;
    }
}

int dbFile::write(void const* buf, size_t size)
{
    ssize_t rc = ::write(fd, buf, size);
    if (rc == -1) { 
	return errno;
    } else if (size_t(rc) != size) { 
	return eof;
    } else { 
	return ok;
    }
}

int dbFile::write(offs_t pos, void const* buf, size_t size)
{  
    ssize_t rc;
#if defined(__svr4__)
    rc = pwrite64(fd, buf, size, pos);
#else
    {
	dbCriticalSection cs(mutex);
	if (offs_t(lseek(fd, pos, SEEK_SET)) != pos) { 
	    return errno;
	}
	rc = ::write(fd, buf, size);
    }
#endif
    if (rc == -1) { 
	return errno;
    } else if (size_t(rc) != size) { 
	return eof;
    } else { 
	return ok;
    }
}

int dbFile::flush() 
{
    return fsync(fd) != ok ? errno : ok;
}

int dbFile::close()
{
    if (fd != -1) { 
	if (::close(fd) == ok) { 
	    fd = -1;
	    return ok;
	} else { 
	    return errno;
	}
    } else { 
	return ok;
    }
}

void* dbFile::allocateBuffer(size_t size) 
{
    return valloc(size);
}

void  dbFile::deallocateBuffer(void* buffer)
{
    free(buffer);
}

#ifdef __linux__
#include <sys/sysinfo.h>
size_t dbFile::ramSize()
{
    struct sysinfo info;
    sysinfo(&info);
    return info.totalram;
} 
#else
size_t dbFile::ramSize()
{
    const size_t minMemorySize = 64000000;
    return minMemorySize;
}
#endif

char* dbFile::errorText(int code, char* buf, size_t bufSize)
{
    switch (code) { 
      case ok:
	strncpy(buf, "No error", bufSize);
	break;
      case eof:
	strncpy(buf, "Transfer less bytes than specified", bufSize);
	break;
      default:
	strncpy(buf, strerror(code), bufSize);
    }
    return buf;
}

#endif

int dbMultiFile::open(int n, dbSegment* seg, int attr)
{
    segment = new dbFileSegment[n];
    nSegments = n;
    while (--n >= 0) { 
	segment[n].size = seg[n].size*dbPageSize;
	int rc = segment[n].open(seg[n].name, attr);
	if (rc != ok) { 
	    while (++n < nSegments) { 
		segment[n].close();
	    }
	    return rc;
	}
    }
    return ok;
}

int dbMultiFile::close() 
{ 
    if (segment != NULL) { 
	for (int i = nSegments; --i >= 0;) { 
	    int rc = segment[i].close();
	    if (rc != ok) { 
		return rc;
	    }
	}
	delete[] segment;
	segment = NULL; 
    }
    return ok;
}
	
int dbMultiFile::flush() 
{ 
    for (int i = nSegments; --i >= 0;) { 
	int rc = segment[i].flush();
	if (rc != ok) { 
	    return rc;
	}
    }
    return ok;
}


int dbMultiFile::write(offs_t pos, void const* ptr, size_t size)
{
    int n = nSegments-1;
    for (int i = 0; i < n; i++) { 
	if (pos < segment[i].size) { 
	    if (pos + size > segment[i].size) { 
		int rc = segment[i].write(pos, ptr, 
					  size_t(segment[i].size - pos));
		if (rc != ok) { 
		    return ok;
		}
		size -= size_t(segment[i].size - pos);
		pos = 0;
	    } else {
		return segment[i].write(pos, ptr, size);
	    }
	} else { 
	    pos -= segment[i].size;
	}
    } 
    return segment[n].write(pos, ptr, size);
}

int dbMultiFile::read(offs_t pos, void* ptr, size_t size)
{
    int n = nSegments-1;
    for (int i = 0; i < n; i++) { 
	if (pos < segment[i].size) { 
	    if (pos + size > segment[i].size) { 
		int rc = segment[i].read(pos, ptr, 
					 size_t(segment[i].size - pos));
		if (rc != ok) { 
		    return ok;
		}
		size -= size_t(segment[i].size - pos);
		pos = 0;
	    } else {
		return segment[i].read(pos, ptr, size);
	    }
	} else { 
	    pos -= segment[i].size;
	}
    } 
    return segment[n].read(pos, ptr, size);
}

