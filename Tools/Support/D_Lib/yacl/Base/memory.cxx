



/*
 *
 *          Copyright (C) 1995, M. A. Sridhar
 *  
 *
 *     This software is Copyright M. A. Sridhar, 1995. You are free
 *     to copy, modify or distribute this software  as you see fit,
 *     and to use  it  for  any  purpose, provided   this copyright
 *     notice and the following   disclaimer are included  with all
 *     copies.
 *
 *                        DISCLAIMER
 *
 *     The author makes no warranties, either expressed or implied,
 *     with respect  to  this  software, its  quality, performance,
 *     merchantability, or fitness for any particular purpose. This
 *     software is distributed  AS IS.  The  user of this  software
 *     assumes all risks  as to its quality  and performance. In no
 *     event shall the author be liable for any direct, indirect or
 *     consequential damages, even if the  author has been  advised
 *     as to the possibility of such damages.
 *
 */






#ifdef __GNUC__
#pragma implementation
#include <string.h>
#endif

#include "base/error.h"
#include "base/memory.h"

#undef new // Have to do this within this scope.

#include <iostream.h>
#include <iomanip.h>

#ifdef __BORLANDC__
    typedef unsigned size_t;
#   include <mem.h>
#elif defined(_MSC_VER)
#   include <memory.h>
#endif


#include <stdlib.h>
#include <malloc.h>

const  ulong magic_cookie = 0xf9a42bb1; // Used to indicate "allocated" state


struct BlockHeader {
    ulong marker;
    long  time;
    BlockHeader* prev;
    BlockHeader* next;
    char*  file;
    long  lineNo;
    long  size;
};

// The HP PA-RISC machines need double-word alignment. Thanks to Remco
// Tijssen (oce-int!ret@rela.nl.net) for the fix.
static const long BlockHeaderSize = sizeof (BlockHeader);

// For debugging only;
// ostream& operator<< (ostream& s, const BlockHeader& hdr)
// {
//     s << "{marker " << hdr.marker << " time " << hdr.time << " prev "
//         << hdr.prev << "\n next " << hdr.next << " file '" << hdr.file <<
//         "' line " << hdr.lineNo << " size " << hdr.size << "\n}" << endl;
//     return s;
// }

#if defined(__GNUC__)
ostream& operator<< (ostream& s, void* p)
{
    s << "0x" << hex << ((ulong) p);
    return s;
}
#endif


// --------------------- Static variables ---------------------------------

static BlockHeader* _AllocListHead = 0; // Head of list of allocated blocks
static BlockHeader* _AllocListTail = 0; // Tail of list of allocated blocks
static short        _LeakCheckerActive = 0;
static long         _Time = 0;          // Clock: ticks on every new and
                                        // delete

static long         _MaxMem = 0;        // Max memory used so far
static long         _CurrentAlloc = 0;  // Amount of memory currently
                                        // allocated
static long         _BeginTime = 0;     // Time at which leack checker was
                                        // instantiated

static void* DoNew (size_t n)
{
    if (n == 0)
        return NULL;
    long size = n;
    // Allocate  extra bytes
    size_t realSize = n + BlockHeaderSize;
    uchar* p = (uchar*) malloc (realSize);
    if (!p) {
        CL_Error::Fatal ("YACL base: allocating %u bytes: no memory!", n);
    }
    _CurrentAlloc += n;
    if (_CurrentAlloc > _MaxMem)
        _MaxMem = _CurrentAlloc;
    BlockHeader* q = (BlockHeader*) p;
    // Put a magic marker
    q->marker = magic_cookie;
    q->time   = _Time++;
    q->lineNo = 0;
    q->file   = "";
    q->size   = size;
    memset (p +BlockHeaderSize,  '\02', (unsigned int) size);
         // Uninitialized allocated memory has 02 in it
    // Insert at tail of allocated list
    if (_AllocListTail) {
        _AllocListTail->next = q;
        q->prev = _AllocListTail;
        q->next = 0;
        _AllocListTail = q;
    }
    else {
        _AllocListHead = _AllocListTail = q;
        q->prev = q->next = 0;
    }
    return p + BlockHeaderSize;
}

void* operator new (size_t n)
{
    return DoNew (n);
}


void* operator new (size_t size, short line_no, const char* file_name)
{
    uchar* p = (uchar*) DoNew (size);
    BlockHeader* q = (BlockHeader*) (p - BlockHeaderSize);
    q->file = (char*) file_name;
    q->lineNo = line_no;
    return p;
}



#if (defined(__GNUC__) && __GNUC_MINOR__ >= 6) ||  \
    (defined(__BORLANDC__) && __BCPLUSPLUS__ >= 0x0320) || \
    defined(__WATCOMC__) || defined(__IBMCPP__)
void* operator new[] (size_t size, short line_no, const char* file_name)
{
    return operator new (size, line_no, file_name);
}
#endif


void operator delete (void* p)
{
    if (!p)
        return; // Do nothing
    BlockHeader* q = (BlockHeader*) ( (uchar*) p - BlockHeaderSize);
    if (q->marker != magic_cookie && _LeakCheckerActive)
        CL_Error::Warning ("YACL op delete (%8lx): memory corrupted", p);
    _CurrentAlloc -= q->size;
    if (_AllocListHead) {
        // Without this test, we get problems with
        // static objects. So we set AllocListHead to
        // zero in LeakChecker's destructor.
        if (q->prev)
            q->prev->next = q->next;
        if (q->next)
            q->next->prev = q->prev;
        if (q == _AllocListHead)
            _AllocListHead = q->next;
        if (q == _AllocListTail)
            _AllocListTail = q->prev;
        memset (q,  '\03', (unsigned int) (BlockHeaderSize + q->size));
            // Freed  memory has 03 in it
    }
    free (q);
    _Time++;
}




CL_MemoryLeakChecker::CL_MemoryLeakChecker (ostream& stream)
: _stream (stream)
{
    _BeginTime = _Time;
}


CL_MemoryLeakChecker::~CL_MemoryLeakChecker ()
{
    if (!_stream.good())
        return;
    if (!_AllocListHead) {
        // _stream << "\n\n\nCL_MemoryLeakChecker: No memory leaks.\n";
        return;
    }
    BlockHeader* q = _AllocListHead;
    long count = 0;
    while (q) {
        if (q->time >= _BeginTime)
            count++;
        q = q->next;
    }
    if (count) {
        _stream << "\n\n\nCL_MemoryLeakChecker: Memory leaks:\n"
                <<       "-----------------------------------\n";
        q = _AllocListHead;
        while (q) {
            if (q->time >= _BeginTime) {
                // Only output if the allocation occurred after the leak
                // checker was created
                _stream << "Time: " <<  /* setw (6) << */ q->time;
                _stream << " Address: " << hex << (void*) q << dec /* <<
                    setfill (' ') */;
                _stream << " Size: " << /* setw (5) << */ q->size << " bytes";
                if (q->lineNo)
                    _stream << " line " << /* setw(3) << */ q->lineNo <<
                        " File: " << q->file;
                _stream << endl;
            }
            q = q->next;
        }
    }
    _AllocListHead = _AllocListTail = 0;
}



long CL_MemoryLeakChecker::MaxMemoryUsed ()
{
    return _MaxMem;
}

long CL_MemoryLeakChecker::CurrentMemoryUsage ()
{
    return _CurrentAlloc;
}



