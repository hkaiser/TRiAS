//-< FILE.CPP >------------------------------------------------------*--------*
// FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
// (Main Memory Database Management System)                          *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// System independent intrface to mapped on memory file
//-------------------------------------------------------------------*--------*

#ifndef __FILE_H__
#define __FILE_H__

class dbFile { 
  protected:
#ifdef _WIN32
    HANDLE fh;
    HANDLE mh;
#else
    int    fd;
#endif
    char*  mmapAddr;
    size_t mmapSize;

  public:
    enum { 
	ok = 0
    };
    //
    // Create backup file
    //
    int    create(char const* name);
    //
    // Open database file and create file mapping object 
    //
    int    open(char const* fileName, char const* sharedName,
		bool readonly, size_t initSize);
    
    void*  getAddr() const { return mmapAddr; }
    size_t getSize() const { return mmapSize; } 
    int    setSize(char const* sharedName, size_t size);
    int    flush();
    int    close();
    int    erase();
    int    write(void const* ptr, size_t& writtenBytes, size_t size);
    int    read(void* ptr, size_t& readBytes, size_t size);

    static char* errorText(int code, char* buf, size_t bufSize);

#ifdef NO_MMAP
    void markAsDirty(size_t pos, size_t size) { 
	size_t page = pos >> pageBits;
	size_t last = (pos + size + pageSize - 1) >> pageBits;
	assert(page >= 0 && (last >> 5) <=  (mmapSize + pageSize*32 - 1) >> (pageBits + 5));
	while (page < last) { 
	    pageMap[page >> 5] |= 1 << (page & 31);
	    page += 1;
	}
    }

  private:
    int* pageMap;
    int  pageMapSize;
    int  pageBits;
    int  pageSize;
#else
    void markAsDirty(size_t, size_t) {}
#endif
};


#endif

