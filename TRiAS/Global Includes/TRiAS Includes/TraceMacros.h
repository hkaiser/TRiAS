// Nützliche Macro's für das interne Debugging --------------------------------
// File: TRACEMACROS.H

#if !defined(_TRACEMACROS_H)
#define _TRACEMACROS_H

#if defined(_DEBUG)
extern "C" DWORD locTraceFlags;		// hier werden TraceFlags abgefragt

#define ADDREF_TRACE(s,c)	\
	if (locTraceFlags & 0x01) TRACE3("[%p]"#s"::AddRef(): %ld -> %ld\r\n",this,c,(c+1))
#define RELEASE_TRACE(s,c)	\
	ASSERT(c > 0);			\
	if (locTraceFlags & 0x01) TRACE3("[%p]"#s"::Release(): %ld -> %ld\r\n",this,c,(c-1))

#define CONSTRUCT_TRACE(s)	\
	if (locTraceFlags & 0x02) TRACE1("[%p]"#s"::"#s"()\r\n",this)
#define DESTRUCT_TRACE(s)	\
	if (locTraceFlags & 0x02) TRACE1("[%p]"#s"::~"#s"()\r\n",this)

#define BASIC_OP_TRACE(s)	\
	if (locTraceFlags & 0x04) TRACE(#s"\r\n")
#define BASIC_OP_TRACE_SYS(s)	\
	if (locTraceFlags & 0x08) TRACE(#s"\r\n")
#define BASIC_OP_TRACE2(s)	\
	if (locTraceFlags & 0x04) { TRACE(s); TRACE("\r\n"); }
#define BASIC_OP_TRACE_SYS2(s)	\
	if (locTraceFlags & 0x08) { TRACE(s); TRACE("\r\n"); }

#else	

#define ADDREF_TRACE(s,c)
#define RELEASE_TRACE(s,c)
#define CONSTRUCT_TRACE(s)
#define DESTRUCT_TRACE(s)
#define BASIC_OP_TRACE(s)
#define BASIC_OP_TRACE_SYS(s)
#define BASIC_OP_TRACE2(s)
#define BASIC_OP_TRACE_SYS2(s)

#endif // _DEBUG

#endif // _TRACEMACROS_H
