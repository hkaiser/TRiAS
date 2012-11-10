//-< FILE.CPP >------------------------------------------------------*--------*
// FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
// (Main Memory Database Management System)                          *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// System dependent implementation of mapped on memory file
//-------------------------------------------------------------------*--------*

#include "stdtp.h"
#include "file.h"

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


int dbFile::open(char const* fileName, char const* sharedName, bool readonly,
		 size_t initSize)
{
    int status;
    fh = CreateFile(fileName, GENERIC_READ|GENERIC_WRITE, 
		    FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, 
		    readonly ? OPEN_EXISTING : OPEN_ALWAYS,
#ifdef NO_MMAP
		    FILE_FLAG_NO_BUFFERING|FILE_FLAG_RANDOM_ACCESS|FILE_FLAG_WRITE_THROUGH,
#else
		    FILE_FLAG_RANDOM_ACCESS|FILE_FLAG_WRITE_THROUGH,
#endif
		    NULL);
    if (fh == INVALID_HANDLE_VALUE) {
	return GetLastError();
    }
    DWORD highSize;
    size_t fileSize = GetFileSize(fh, &highSize);
    if (fileSize == BAD_POS && (status = GetLastError()) != ok) {
	CloseHandle(fh);
	return status;
    }
    assert(highSize == 0);
    
    mmapSize = fileSize;
    if (!readonly && fileSize < initSize) { 
	mmapSize = initSize;
    }
#ifdef  NO_MMAP
    mmapAddr = (char*)VirtualAlloc(NULL, mmapSize, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
    DWORD readBytes;
    if (mmapAddr == NULL
	|| !ReadFile(fh, mmapAddr, fileSize, &readBytes, NULL) || readBytes != fileSize) 
    {  
	status = GetLastError();
	CloseHandle(fh);
	return status;
    } 
    memset(mmapAddr+fileSize, 0, mmapSize - fileSize);
    pageBits = 12;
    pageSize = 1 << pageBits;
    pageMapSize = (mmapSize + pageSize*32 - 1) >> (pageBits + 5);
    pageMap = new int[pageMapSize];
    memset(pageMap, 0, pageMapSize*sizeof(int));
    mh = NULL;
#else
    mh = CreateFileMapping(fh, NULL, PAGE_READWRITE, 0, mmapSize, sharedName);
    status = GetLastError();
    if (mh == NULL) { 
	CloseHandle(fh);
	return status;
    }
    mmapAddr = (char*)MapViewOfFile(mh, readonly 
				    ? FILE_MAP_READ : FILE_MAP_ALL_ACCESS, 
				    0, 0, 0);
    if (mmapAddr == NULL) { 
	status = GetLastError();
	CloseHandle(mh);
	CloseHandle(fh);
	return status;
    } 
    if (status != ERROR_ALREADY_EXISTS && mmapSize > fileSize 
	&& osinfo.dwPlatformId != VER_PLATFORM_WIN32_NT) 
    { 
	// Windows 95 doesn't initialize pages
	memset(mmapAddr+fileSize, 0, mmapSize - fileSize);
    }
#endif
    return ok; 
}


int dbFile::create(const char* name)
{
    fh = CreateFile(name, GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 
		    FILE_FLAG_NO_BUFFERING|FILE_FLAG_SEQUENTIAL_SCAN, NULL); 
    if (fh == INVALID_HANDLE_VALUE) {
	return GetLastError();
    }
    mh = NULL;
    mmapAddr = NULL;
    return ok;
}

int dbFile::read(void* buf, size_t& readBytes, size_t size)
{  
    DWORD count;
    if (ReadFile(fh, buf, size, &count, NULL)) { 
	readBytes = count;
	return ok;
    } else { 
	readBytes = 0;
	return GetLastError();
    }
}

int dbFile::write(void const* buf, size_t& writtenBytes, size_t size)
{  
    DWORD count;
    if (WriteFile(fh, buf, size, &count, NULL)) { 
	writtenBytes = count;
	return ok;
    } else { 
	writtenBytes = 0;
	return GetLastError();
    }
}


int dbFile::flush()
{
#ifdef NO_MMAP
    int* map = pageMap;
    for (int i = 0, n = pageMapSize; i < n; i++) { 
	if (map[i] != 0) { 
	    size_t pos = (size_t)i << (pageBits + 5);
	    unsigned mask = map[i];
	    int count = 0;
	    do { 
		int size = 0;
		while ((mask & 1) == 0) { 
		    pos += pageSize;
		    mask >>= 1;
		    count += 1;
		}
		while (true) { 
		    do { 
			size += pageSize;
			mask >>= 1;
			count += 1;
		    } while ((mask & 1) != 0);

		    if (i+1 < n && count == 32 && (map[i+1] & 1) != 0) { 
			map[i] = 0;
			mask = map[++i];
			count = 0;
		    } else { 
			break;
		    }
		}
		DWORD written;
		if (SetFilePointer(fh, pos, NULL, FILE_BEGIN) != pos ||
		    !WriteFile(fh, mmapAddr + pos, size, &written, NULL) 
		    || written != (DWORD)size) 
		{ 
		    return GetLastError();
		}
		pos += size;
	    } while (mask != 0);
	    map[i] = 0;
	}
    }
    return ok;
#else
    if (FlushViewOfFile(mmapAddr, mmapSize)) { 
	return ok;
    } else { 
	return GetLastError();
    }
#endif
}

int dbFile::setSize(char const* sharedName, size_t size)
{
#ifdef NO_MMAP
    char* newBuf = (char*)VirtualAlloc(NULL, size, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
    if (newBuf == NULL) { 
	return GetLastError();
    }
    memcpy(newBuf, mmapAddr, mmapSize);
    VirtualFree(mmapAddr, 0, MEM_RELEASE);
    mmapAddr = newBuf;
    mmapSize = size;
    int newPageMapSize = (size + pageSize*32 - 1) >> (pageBits + 5);
    int* newPageMap = new int[newPageMapSize];
    memcpy(newPageMap, pageMap, pageMapSize*sizeof(int));
    memset(newPageMap + pageMapSize, 0, 
	   (newPageMapSize-pageMapSize)*sizeof(int));
    delete[] pageMap;
    pageMapSize = newPageMapSize;    
    pageMap = newPageMap;    
#else
    if (!UnmapViewOfFile(mmapAddr) || !CloseHandle(mh)) { 
	return GetLastError();
    } 
    mh = CreateFileMapping(fh, NULL, PAGE_READWRITE, 0, size, sharedName);
    int status = GetLastError();
    if (mh == NULL) { 
	return status;
    }
    mmapAddr = (char*)MapViewOfFile(mh, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (mmapAddr == NULL) { 
	return GetLastError();
    }
    if (status != ERROR_ALREADY_EXISTS 
	&& osinfo.dwPlatformId != VER_PLATFORM_WIN32_NT) 
    {
	// Windows 95 doesn't initialize pages
	memset(mmapAddr+mmapSize, 0, size - mmapSize);
    } 
    mmapSize = size;
#endif
    return ok;
}

int dbFile::close()
{
    if (mmapAddr != NULL) { 
#ifdef NO_MMAP
	int rc = flush();
	if (rc != ok) { 
	    return rc;
	}
	VirtualFree(mmapAddr, 0, MEM_RELEASE);    
	delete[] pageMap;
#else
	if (!UnmapViewOfFile(mmapAddr)) { 
	    return GetLastError();
	}
#endif
    }
    if (mh != NULL) { 
	if (!CloseHandle(mh)) {
	    return GetLastError();
	}
    }
    return CloseHandle(fh) ? ok : GetLastError();
}

char* dbFile::errorText(int code, char* buf, size_t bufSize)
{
    int len = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
			    NULL,
			    code,
			    0,
			    buf,
			    bufSize,
			    NULL);
    if (len == 0) { 
	char errcode[64];
	sprintf(errcode, "unknown error code %u", code);
	strncpy(buf, errcode, bufSize);
    }
    return buf;
}

#else // Unix

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#ifndef NO_MMAP
#include <sys/mman.h>
#endif

#ifndef O_SYNC
#define O_SYNC	O_FSYNC
#endif

#ifndef O_DSYNC
#define O_DSYNC O_SYNC
#endif


int dbFile::open(char const* name, char const*, bool readonly, size_t initSize)
{
    int status;
    fd = ::open(name, readonly ? O_RDONLY : O_RDWR/*|O_DSYNC*/|O_CREAT, 0666);
    if (fd < 0) { 
	return errno;
    }
    mmapSize = lseek(fd, 0, SEEK_END); 
#ifdef NO_MMAP
    size_t fileSize = mmapSize;
    if (!readonly && mmapSize < initSize) { 
	mmapSize = initSize;
    }
    mmapAddr = (char*)valloc(mmapSize);
    if (mmapAddr == NULL) { 
	status = errno;
	::close(fd);
	return status;
    }
    lseek(fd, 0, SEEK_SET); 
    if ((size_t)::read(fd, mmapAddr, fileSize) != fileSize) { 
	free(mmapAddr);
	mmapAddr = NULL;
	status = errno;
	::close(fd);
	return status;
    }
    pageSize = getpagesize();
    pageBits = 9;
    while ((1 << pageBits) < pageSize) { 
	pageBits += 1;
    }
    pageMapSize = (mmapSize + pageSize*32 - 1) >> (pageBits + 5);
    pageMap = new int[pageMapSize];
    memset(pageMap, 0, pageMapSize*sizeof(int));
#else    
    if (!readonly && mmapSize < initSize) { 
	mmapSize = initSize;
	if (ftruncate(fd, mmapSize) != ok) {
	    status = errno;
	    ::close(fd);
	    return status;
	}
    }
    mmapAddr = (char*)mmap(NULL, mmapSize, 
			   readonly ? PROT_READ : PROT_READ|PROT_WRITE, 
			   MAP_SHARED, fd, 0);
    if (mmapAddr == (char*)-1) { 
	status = errno;
	mmapAddr = NULL;
	::close(fd);
	return status;
    }
#endif
    return ok;
}

int dbFile::create(const char* name)
{
    mmapAddr = NULL;
    fd = ::open(name, O_RDWR|O_TRUNC|O_CREAT, 0666);
    if (fd < 0) { 
	return errno;
    }
    return ok;
}

int dbFile::read(void* buf, size_t& readBytes, size_t size)
{  
    long rc = ::read(fd, buf, size);
    if (rc < 0) { 
	readBytes = 0;
	return errno;
    }
    readBytes = rc;
    return ok;
}

int dbFile::write(void const* buf, size_t& writtenBytes, size_t size)
{  
    long rc = ::write(fd, buf, size);
    if (rc < 0) { 
	writtenBytes = 0;
	return errno;
    }
    writtenBytes = rc;
    return ok;
}

int dbFile::setSize(char const*, size_t size)
{
#ifdef NO_MMAP
    char* newBuf = (char*)valloc(size);
    if (newBuf == NULL) { 
	return errno;
    }
    memcpy(newBuf, mmapAddr, mmapSize);
    free(mmapAddr);
    mmapAddr = newBuf;
    mmapSize = size;
    int newPageMapSize = (size + pageSize*32 - 1) >> (pageBits + 5);
    int* newPageMap = new int[newPageMapSize];
    memcpy(newPageMap, pageMap, pageMapSize*sizeof(int));
    memset(newPageMap + pageMapSize, 0, 
	   (newPageMapSize-pageMapSize)*sizeof(int));
    delete[] pageMap;
    pageMapSize = newPageMapSize;    
    pageMap = newPageMap;    
#else
    if (munmap(mmapAddr, mmapSize) != ok ||
	ftruncate(fd, size) != ok ||
	(mmapAddr = (char*)mmap(NULL, size, PROT_READ|PROT_WRITE,
				MAP_SHARED, fd, 0)) == (char*)-1)
    {	
	return errno;
    }
#endif
    mmapSize = size;
    return ok;
}

int dbFile::flush() 
{
#ifdef NO_MMAP
    int* map = pageMap;
    for (int i = 0, n = pageMapSize; i < n; i++) { 
	if (map[i] != 0) { 
	    size_t pos = (size_t)i << (pageBits + 5);
	    unsigned mask = map[i];
	    do { 
		int size = 0;
		while ((mask & 1) == 0) { 
		    pos += pageSize;
		    mask >>= 1;
		}
		do { 
		    size += pageSize;
		    mask >>= 1;
		} while ((mask & 1) != 0);
		if (::write(fd, mmapAddr + pos, size) != size) { 
		    return errno;
		}
		pos += size;
	    } while (mask != 0);
	    map[i] = 0;
	}
    }
#else
    if (msync(mmapAddr, mmapSize, MS_SYNC) != ok) { 
	return errno;
    }
#endif
    return ok;
}

int dbFile::close()
{
    if (mmapAddr != NULL) { 
#ifdef NO_MMAP
	int rc = flush();
	if (rc != ok) { 
	    return rc;
	}
	free(mmapAddr);    
	delete[] pageMap;
#else
	if (munmap(mmapAddr, mmapSize) != ok) { 
	    return errno;
	}
#endif
	mmapAddr = NULL;
    }
    return ::close(fd) != ok ? errno : ok;
}

char* dbFile::errorText(int code, char* buf, size_t bufSize)
{
    return strncpy(buf, strerror(code), bufSize);
}

#endif

