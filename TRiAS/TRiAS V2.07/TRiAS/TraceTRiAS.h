// Flags für Trace von TRiAS
// File: TRACETRIAS.H

#if !defined(_TRACETRIAS_H)
#define _TRACETRIAS_H

#if defined(_DEBUG)

extern DWORD g_dwTraceLevel;

#define TRACE_NOTRACE		0

#define TRACE_LEVEL1		1	// Modifizierende Befehle
#define TRACE_LEVEL2		2	// Enumerationen
#define TRACE_LEVEL3		3	// Befehle, die nichts in der GeoDB ändern
#define TRACE_LEVEL4		4	// Abfragen aller Art

const char g_cbTraceLevel[] = TEXT("TraceLevel");

#endif // _DEBUG
#endif // _TRACETRIAS_H
