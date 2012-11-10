#if !defined(lint) && !defined(_NOIDENT)
static const char* rcsid = "@(#)$RCSfile: dh_pipe.c,v $ $Revision: 1.1.2.1 $ (DOWNHILL) $Date: 1997/04/17 06:17:28 $";
#endif

#include <stdlib.h>
#include <io.h>
#include <errno.h>
#include <fcntl.h>



int pipe(int handle[2], int inherit[2], int bufferSize, int mode )
{
    int inheritable;
    if (_pipe(handle, bufferSize, mode | O_NOINHERIT) < 0) {
	return -1;
    }
    
    if (inherit[0]) {
	if ((inheritable = _dup(handle[0])) < 0) {
	    close(handle[0]);
	    close(handle[1]);
	    return -1;
	}
	close(handle[0]);
	handle[0] = inheritable;
    }
    if (inherit[1]) {
	if ((inheritable = _dup(handle[1])) < 0) {
	    close(handle[0]);
	    close(handle[1]);
	    return -1;
	}
	close(handle[1]);
	handle[1] = inheritable;
    }
    return 0;
}
