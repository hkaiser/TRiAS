#ifndef _DOWNHILL_SYS_UIO_H
#define _DOWNHILL_SYS_UIO_H

#include <sys/types.h>

struct iovec {
    void*	iov_base;
    size_t	iov_len;
};

int readv(int, struct iovec *, int);
int writev(int, struct iovec *, int);

#endif /* _DOWNHILL_SYS_UIO_H */
