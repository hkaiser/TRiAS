



#ifndef _memory_h_ /* Sat Aug 27 13:59:50 1994 */
#define _memory_h_




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
#pragma interface
#endif


#include <stddef.h>
#include "base/defs.h"



// Create an instance of MemoryLeakChecker in any scope in which leaks must
// be checked. When this object is destroyed, it prints a record of all
// currently  allocated blocks onto the stream. For example, in the code:
//
// \begin{verbatim}
//      #include <iostream.h>
//      main ()
//      {
//          CL_MemoryLeakChecker chk (cout);
//          ...
//      }
// \end{verbatim}
//
// \noindent
// all blocks still allocated at the end of the main program are printed on
// {\tt cout}.

#if defined(__BORLANDC__) && (defined(__MS_DOS__) || defined(__MS_WINDOWS__))
class  _CLASSTYPE ostream;
#else
class   ostream;
#endif


class YACL_BASE CL_MemoryLeakChecker {
public:
    CL_MemoryLeakChecker (ostream& stream);

    ~CL_MemoryLeakChecker ();

    static long CurrentMemoryUsage ();
    // Return the amount of memory currently allocated.
    
    static long MaxMemoryUsed ();
    // Return the maximum amount of memory used so far by this application,
    // since the time that this MemoryLeakChecker was created.
    
protected:
    ostream& _stream;
    
};

void* operator new (size_t size, short line_no, const char*
                    file_name);

#if (defined(__GNUC__) && __GNUC_MINOR__ >= 6) || defined(__IBMCPP__) || \
  (defined(__BORLANDC__) && __BCPLUSPLUS__ >= 0x0320) || defined(__WATCOMC__)
void* operator new[] (size_t size, short line_no, const char* file_name);
#endif


#define new new(__LINE__, __FILE__)

#endif /* _memory_h_ */
