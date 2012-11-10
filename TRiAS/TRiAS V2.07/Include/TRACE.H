// Nützliche Macro's für das interne Debugging --------------------------------
// File: TRACE.H

#if !defined(_TRACE_H)
#define _TRACE_H

#if defined(_DEBUG)
extern "C" DWORD locTraceFlags;		// hier werden TraceFlags abgefragt

#define ADDREF_TRACE(s,c)	\
	if (locTraceFlags & 0x01) TRACE3("[%p]"#s"::AddRef(): %ld -> %ld",this,c,(c+1))
#define RELEASE_TRACE(s,c)	\
	ASSERT(c > 0);			\
	if (locTraceFlags & 0x01) TRACE3("[%p]"#s"::Release(): %ld -> %ld",this,c,(c-1))

#define CONSTRUCT_TRACE(s)	\
	if (locTraceFlags & 0x02) TRACE1("[%p]"#s"::"#s"()",this)
#define DESTRUCT_TRACE(s)	\
	if (locTraceFlags & 0x02) TRACE1("[%p]"#s"::~"#s"()",this)

#define BASIC_OP_TRACE(s)	\
	if (locTraceFlags & 0x04) TRACE(#s)
#define BASIC_OP_TRACE_SYS(s)	\
	if (locTraceFlags & 0x08) TRACE(#s)

#else	

#define ADDREF_TRACE(s,c)
#define RELEASE_TRACE(s,c)
#define CONSTRUCT_TRACE(s)
#define DESTRUCT_TRACE(s)
#define BASIC_OP_TRACE(s)
#define BASIC_OP_TRACE_SYS(s)

#endif // _DEBUG

#endif // _TRACE_H
