#ifndef __SHALLOC_H
#define __SHALLOC_H

#ifdef _DEBUG

#define DEBUG_NEW new(__FILE__, __LINE__)
//#define DEBUG_NEW new

void* __cdecl operator new(size_t nSize, char *lpszFileName, int nLine);
void __cdecl operator delete(void* p, char *lpszFileName, int nLine);

#include <crtdbg.h>
#include <tstring>

class CAllocationGuarder
{
public:
	CAllocationGuarder( const char *szFile, int nLine );
    ~CAllocationGuarder();
	void Report();
	void ResetState( const char *szFile, int nLine );
	string m_strLine;
	string m_strFile;
	_CrtMemState m_MemState;
};


void *DebugMalloc( size_t nSize, char *szFile, int nLine );

#define SHALLOC_BEGIN_GUARD() { CAllocationGuarder Guarder(__FILE__, __LINE__); 
#define SHALLOC_END_GUARD() } 

#else
#define SHALLOC_BEGIN_GUARD()
#define SHALLOC_END_GUARD() 
#endif


#endif
