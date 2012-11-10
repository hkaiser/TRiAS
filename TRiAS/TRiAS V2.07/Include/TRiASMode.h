// Flags und Variable zu TRiASMode
// File: TRiASMode.h

///////////////////////////////////////////////////////////////////////////////
// Flags aus Registry, die über den Mode von FakeMFC/TRiAS entscheiden 
#define TRIASMODE_SubClassTRiAS		0x01
#define TRIASMODE_HookTRiAS			0x02
#define TRIASMODE_SubClassTRiASView	0x04

#define TRIASMODE_NativeDB			0x00	// Default
#define TRIASMODE_GDO				0x08

extern DWORD g_dwTRiASMode;					// TRiASMode

