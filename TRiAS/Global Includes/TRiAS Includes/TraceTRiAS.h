///////////////////////////////////////////////////////////////////////////
// Flags für Trace von TRiAS
// TraceTRiAS.h

#if !defined(_TRACETRIAS_H__A37D8264_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
#define _TRACETRIAS_H__A37D8264_4A3F_11d1_96DC_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if defined(_DEBUG)

extern DWORD g_dwTraceLevel;

#define TRACE_NOTRACE		0

#define TRACE_LEVEL1		1	// Modifizierende Befehle
#define TRACE_LEVEL2		2	// Enumerationen
#define TRACE_LEVEL3		3	// Befehle, die nichts in der GeoDB ändern
#define TRACE_LEVEL4		4	// Abfragen aller Art

const char g_cbTraceLevel[] = TEXT("TraceLevel");

#endif // _DEBUG

#endif // !defined(_TRACETRIAS_H__A37D8264_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
