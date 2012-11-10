/*
 * HISTORY
 * 	Add uio calls: readv, writev.
 * 	Make libdownhill installable.
 * 	Put include guards around stdlib.h.
 * 	[1997/05/21  07:36:00  tbartley]
 */
#include <sys/uio.h>
#include <unistd.h>

int readv(int fd, struct iovec* iov, int iovcount)
{
    int i;
    int cc;
    int length = 0;
    for (i = 0; i < iovcount; ++i) {
	cc = read(fd, iov[i].iov_base, iov[i].iov_len);
	if (cc == -1) {
	    return -1;
	}
	length += cc;
	if (cc < (int)iov[i].iov_len) {
	    break;
	}
    }
    return length;
}

int writev(int fd, struct iovec* iov, int iovcount)
{
    int i;
    int cc;
    int length;
    length = 0;
    for (i = 0; i < iovcount; ++i) {
	cc = write(fd, iov[i].iov_base, iov[i].iov_len);
	if (cc == -1) {
	    return -1;
	}
	length += cc;
	if (cc < (int)iov[i].iov_len) {
	    break;
	}
    }
    return length;
}
