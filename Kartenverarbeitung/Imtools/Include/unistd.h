#include <io.h>
#include <fcntl.h>

#define IsWriteOnly(_stream) ((_stream)->_flag & _IOWRT)