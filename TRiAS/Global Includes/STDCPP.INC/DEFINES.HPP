// defined standard header
#ifndef _DEFINES_
#define _DEFINES_

#ifndef _YXVALS_
#include <yxvals.h>
#endif

// type definitions
	typedef void fvoid_t (void);

#ifndef _PTRDIFFT
	#define _PTRDIFFT
	typedef _Ptrdifft ptrdiff_t;
#endif // _PTRDIFFT
#ifndef _SIZET
	#define _SIZET
	typedef _Sizet size_t;
#endif // _SIZET
#ifndef _WCHART
	#define _WCHART
	typedef _Wchart wchar_t;
#endif // _WCHART
#ifndef _WINTT
	#define _WINTT
	typedef _Wintt wint_t;
#endif // _WINTT
enum capacity { default_size, reserve };

// constants
const size_t NPOS = (size_t)(-1);

// functions
void _Nomemory (void);

#endif // _DEFINES_
