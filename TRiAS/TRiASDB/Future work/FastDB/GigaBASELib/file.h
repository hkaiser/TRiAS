//-< FILE.CPP >------------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 30-Jan-99    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// System independent intrface to operating system file
//-------------------------------------------------------------------*--------*

#ifndef __FILE_H__
#define __FILE_H__

class dbFile { 
  protected:
#ifdef _WIN32
    HANDLE fh;
#else
    int    fd;
#endif
    dbMutex mutex;
  public:
    enum ReturnStatus { 
	ok  = 0,
	eof = -1 // number of read/written bytes is smaller than requested
    };
    enum OpenAttributes { 
	read_only  = 0x01,
	truncate   = 0x02,
        sequential = 0x04   
    };
    int open(char const* fileName, int attr);
    int write(void const* ptr, size_t size);
    int read(void* ptr, size_t size);

    dbFile();
    virtual ~dbFile();

    virtual int flush();
    virtual int close();

    virtual int write(offs_t pos, void const* ptr, size_t size);
    virtual int read(offs_t pos, void* ptr, size_t size);

    static void* allocateBuffer(size_t bufferSize);
    static void  deallocateBuffer(void* buffer);

    static size_t ramSize();

    static char* errorText(int code, char* buf, size_t bufSize);
};


class dbMultiFile : public dbFile { 
  public:
    struct dbSegment { 
	char*   name;
	offs_t  size;
    };
    
    int open(int nSegments, dbSegment* segments, int attr);

    virtual int flush();
    virtual int close();

    virtual int write(offs_t pos, void const* ptr, size_t size);
    virtual int read(offs_t pos, void* ptr, size_t size);

    dbMultiFile() { segment = NULL; }
    ~dbMultiFile() {}

  protected:
    class dbFileSegment : public dbFile { 
      public:
	offs_t size;
    };
    int            nSegments;
    dbFileSegment* segment;
};


#endif
