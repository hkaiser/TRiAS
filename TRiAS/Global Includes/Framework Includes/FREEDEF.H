#if defined(__BCPLUSPLUS__)
#define DLLENTRY __export
#define LOADDS __loadds __export
#elif defined(__WATCOMC__)
#define DLLENTRY	__export
#define LOADDS
#else
#define DLLENTRY	__export
#define LOADDS
#endif
