
#ifndef _error_h_
#define _error_h_





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

#include "base/defs.h"


// This class is an encapsulation of a simple error-handling
// mechanism. The {\tt Warning} and {\tt Fatal} methods accept parameters in
// the same style as {\tt printf} does. For example, you can write
//
// {\small \begin{verbatim}
//          CL_Error::Warning ("Bad array bound %d limit %d", i, n);
//\end{verbatim}
// }
//
// The {\tt Warning} method formats the string, and then invokes the warning
// handler with the formatted string. The default warning handler
// simply prints out the message.
//
// The {\tt Fatal} method behaves similarly. It invokes the fatal-error
// handler, and exits the program if the latter returns TRUE.
//
// The {\tt SetWarningHandler} and {\tt SetFatalHandler} methods can be used to
// provide user-specific warning and fatal handlers instead of the
// default ones. These methods return the previous values for their handlers.


//[ Global
typedef bool (*CL_ErrorHandler) (const char* message);
// ErrorHandler is the function prototype needed by the
// error-handler-setting methods.
//] Global


class YACL_BASE CL_Error {

public:

    static void Warning (const char *fmt, ...);
    // Treat the parameter list as if it were the parameter list to a {\tt
    // printf}, and format it accordingly. Call the current warning
    // handler with the resulting string.

    static void Fatal   (const char *fmt, ...);
    // Treat the parameter list as if it were the parameter list to a {\tt
    // printf}, and format it accordingly. Call the current fatal error
    // handler with the resulting string. If the handler returns TRUE,
    // terminate the application via {\tt exit}.


    static CL_ErrorHandler SetWarningHandler    (CL_ErrorHandler handler);
    // Set the current warning handler to the parameter. This function
    // returns the previous handler.
    
    static CL_ErrorHandler SetFatalErrorHandler (CL_ErrorHandler handler);
    // Set the current fatal error handler to the parameter. This function
    // returns the previous handler.
    
    
};

#endif
